#include "mcp_cli_bridge.h"

#include "aura/mcp/mcp_envelope.h"
#include "aura/safety/protected_export.h"
#include "mcp_cli_bridge_internal.h"
#include "mcp_path_policy.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <cerrno>
#include <csignal>
#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace {

namespace fs = std::filesystem;

constexpr const char* kToolSchemaVersion = "protected/1.0";
constexpr const char* kDisclosure = "protected";
constexpr std::size_t kStdoutCap = 1024 * 1024;
constexpr std::size_t kStderrCap = 64 * 1024;
constexpr int kCliTimeoutMs = 30000;

struct CliResult {
    bool        spawned = false;
    bool        timed_out = false;
    bool        stdout_truncated = false;
    bool        stderr_truncated = false;
    int         exit_code = -1;
    std::string stdout_text;
    std::string stderr_text;
    std::string error_message;
};

struct CliArg {
    std::string narrow;
#ifdef _WIN32
    std::wstring wide;
#endif
};

bool streq(const char* lhs, const char* rhs) {
    return lhs != nullptr && rhs != nullptr && std::string(lhs) == rhs;
}

bool nonempty(const char* value) {
    return value != nullptr && value[0] != '\0';
}

fs::path pathFromUtf8(const char* value) {
    if (value == nullptr) {
        return {};
    }
    return fs::u8path(value);
}

std::string getenvString(const char* name) {
    const char* value = std::getenv(name);
    return value != nullptr ? std::string(value) : std::string();
}

fs::path cliName() {
#ifdef _WIN32
    return "aura.exe";
#else
    return "aura";
#endif
}

std::vector<fs::path> candidateCliPaths(const fs::path& root) {
    const fs::path exe = cliName();
    return {
        root / "build-trim-gui" / "src" / "cli" / "Release" / exe,
        root / "build-trim-gui" / "src" / "cli" / exe,
        root / "build" / "src" / "cli" / "Release" / exe,
        root / "build" / "src" / "cli" / exe,
        root / "src" / "cli" / "Release" / exe,
        root / "src" / "cli" / exe,
    };
}

fs::path locateAuraCli() {
    std::error_code ec;
    const std::string env_root = getenvString("AURA_REPO_ROOT");
    const fs::path root =
        env_root.empty() ? fs::current_path(ec) : pathFromUtf8(env_root.c_str());
    if (root.empty() || ec) {
        return {};
    }

    for (const fs::path& candidate : candidateCliPaths(root)) {
        if (fs::is_regular_file(candidate, ec) && !ec) {
            return candidate;
        }
        ec.clear();
    }
    return {};
}

std::string trimForMessage(std::string value, std::size_t cap = 512) {
    value.erase(value.begin(),
                std::find_if(value.begin(), value.end(), [](unsigned char ch) {
                    return ch != '\r' && ch != '\n' && ch != '\t' &&
                           ch != ' ';
                }));
    value.erase(std::find_if(value.rbegin(), value.rend(),
                             [](unsigned char ch) {
                                 return ch != '\r' && ch != '\n' &&
                                        ch != '\t' && ch != ' ';
                             })
                    .base(),
                value.end());
    if (value.size() > cap) {
        value.resize(cap);
        value += "...";
    }
    return value;
}

CliArg literalArg(const char* value) {
    CliArg arg;
    arg.narrow = value != nullptr ? value : "";
#ifdef _WIN32
    for (const char ch : arg.narrow) {
        arg.wide.push_back(static_cast<unsigned char>(ch));
    }
#endif
    return arg;
}

CliArg pathArg(const fs::path& path) {
    CliArg arg;
    arg.narrow = path.string();
#ifdef _WIN32
    arg.wide = path.wstring();
#endif
    return arg;
}

#ifdef _WIN32

struct UniqueHandle {
    HANDLE handle = NULL;

    UniqueHandle() = default;
    explicit UniqueHandle(HANDLE value) : handle(value) {}
    ~UniqueHandle() {
        reset();
    }

    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    bool valid() const {
        return handle != NULL && handle != INVALID_HANDLE_VALUE;
    }

    HANDLE get() const {
        return handle;
    }

    HANDLE release() {
        HANDLE value = handle;
        handle = NULL;
        return value;
    }

    void reset(HANDLE value = NULL) {
        if (valid()) {
            CloseHandle(handle);
        }
        handle = value;
    }
};

bool needsWindowsQuoting(const std::wstring& arg) {
    if (arg.empty()) {
        return true;
    }
    for (const wchar_t ch : arg) {
        if (ch == L' ' || ch == L'\t' || ch == L'\n' || ch == L'\v' ||
            ch == L'"') {
            return true;
        }
    }
    return false;
}

std::wstring quoteWindowsArg(const std::wstring& arg) {
    if (!needsWindowsQuoting(arg)) {
        return arg;
    }

    std::wstring quoted = L"\"";
    std::size_t backslashes = 0;
    for (const wchar_t ch : arg) {
        if (ch == L'\\') {
            ++backslashes;
            continue;
        }
        if (ch == L'"') {
            quoted.append(backslashes * 2 + 1, L'\\');
            quoted += L'"';
            backslashes = 0;
            continue;
        }
        quoted.append(backslashes, L'\\');
        backslashes = 0;
        quoted += ch;
    }
    quoted.append(backslashes * 2, L'\\');
    quoted += L'"';
    return quoted;
}

std::wstring buildCommandLine(const fs::path& exe,
                              const std::vector<CliArg>& args) {
    std::wstring command = quoteWindowsArg(exe.wstring());
    for (const CliArg& arg : args) {
        command += L' ';
        command += quoteWindowsArg(arg.wide);
    }
    return command;
}

struct PipeCapture {
    HANDLE      handle = NULL;
    std::size_t cap = 0;
    bool        truncated = false;
    std::string output;
};

DWORD WINAPI readerThread(LPVOID param) {
    auto* capture = static_cast<PipeCapture*>(param);
    char buffer[8192];
    DWORD read = 0;

    for (;;) {
        const BOOL ok =
            ReadFile(capture->handle, buffer, sizeof(buffer), &read, NULL);
        if (!ok || read == 0) {
            break;
        }
        const std::size_t available =
            capture->output.size() < capture->cap
                ? capture->cap - capture->output.size()
                : 0;
        const std::size_t copy =
            std::min<std::size_t>(available, static_cast<std::size_t>(read));
        if (copy > 0) {
            capture->output.append(buffer, copy);
        }
        if (copy < static_cast<std::size_t>(read)) {
            capture->truncated = true;
        }
    }
    return 0;
}

bool setKillOnJobClose(HANDLE job) {
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION info;
    ZeroMemory(&info, sizeof(info));
    info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    return SetInformationJobObject(
               job, JobObjectExtendedLimitInformation, &info, sizeof(info)) !=
           FALSE;
}

bool finishReaderThread(HANDLE        thread,
                        UniqueHandle& pipe,
                        PipeCapture*  capture,
                        std::string&  output,
                        bool&         truncated,
                        std::string&  error) {
    if (capture == nullptr) {
        return true;
    }
    if (thread == NULL) {
        delete capture;
        return true;
    }
    DWORD waited = WaitForSingleObject(thread, 2000);
    if (waited != WAIT_OBJECT_0) {
        CancelIoEx(pipe.get(), NULL);
        CancelSynchronousIo(thread);
        waited = WaitForSingleObject(thread, 2000);
    }
    if (waited == WAIT_OBJECT_0) {
        output = std::move(capture->output);
        truncated = capture->truncated;
        delete capture;
        CloseHandle(thread);
        return true;
    }

    if (error.empty()) {
        error = "pipe reader cleanup timed out";
    }
    pipe.release();
    CloseHandle(thread);
    return false;
}

CliResult runAuraCli(const fs::path& exe, const std::vector<CliArg>& args) {
    CliResult result;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    UniqueHandle stdout_read;
    UniqueHandle stdout_write;
    UniqueHandle stderr_read;
    UniqueHandle stderr_write;
    UniqueHandle stdin_read;
    UniqueHandle job(CreateJobObjectW(NULL, NULL));
    if (!job.valid()) {
        result.error_message = "CreateJobObject failed";
        return result;
    }
    if (!setKillOnJobClose(job.get())) {
        result.error_message = "SetInformationJobObject failed";
        return result;
    }

    HANDLE raw_stdout_read = NULL;
    HANDLE raw_stdout_write = NULL;
    HANDLE raw_stderr_read = NULL;
    HANDLE raw_stderr_write = NULL;

    if (!CreatePipe(&raw_stdout_read, &raw_stdout_write, &sa, 0)) {
        result.error_message = "CreatePipe(stdout) failed";
        return result;
    }
    stdout_read.reset(raw_stdout_read);
    stdout_write.reset(raw_stdout_write);
    SetHandleInformation(stdout_read.get(), HANDLE_FLAG_INHERIT, 0);

    if (!CreatePipe(&raw_stderr_read, &raw_stderr_write, &sa, 0)) {
        result.error_message = "CreatePipe(stderr) failed";
        return result;
    }
    stderr_read.reset(raw_stderr_read);
    stderr_write.reset(raw_stderr_write);
    SetHandleInformation(stderr_read.get(), HANDLE_FLAG_INHERIT, 0);

    stdin_read.reset(CreateFileW(L"NUL",
                                 GENERIC_READ,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 &sa,
                                 OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL));
    if (!stdin_read.valid()) {
        result.error_message = "CreateFileW(NUL) failed";
        return result;
    }

    SIZE_T attr_size = 0;
    InitializeProcThreadAttributeList(NULL, 1, 0, &attr_size);
    std::vector<unsigned char> attr_storage(attr_size);
    auto* attr_list =
        reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>(attr_storage.data());
    if (!InitializeProcThreadAttributeList(attr_list, 1, 0, &attr_size)) {
        result.error_message = "InitializeProcThreadAttributeList failed";
        return result;
    }

    HANDLE inherited_handles[] = {
        stdout_write.get(),
        stderr_write.get(),
        stdin_read.get(),
    };
    if (!UpdateProcThreadAttribute(attr_list,
                                   0,
                                   PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
                                   inherited_handles,
                                   sizeof(inherited_handles),
                                   NULL,
                                   NULL)) {
        DeleteProcThreadAttributeList(attr_list);
        result.error_message = "UpdateProcThreadAttribute(handle list) failed";
        return result;
    }

    std::wstring command = buildCommandLine(exe, args);
    std::vector<wchar_t> command_buf(command.begin(), command.end());
    command_buf.push_back(L'\0');

    STARTUPINFOEXW si;
    ZeroMemory(&si, sizeof(si));
    si.StartupInfo.cb = sizeof(si);
    si.StartupInfo.dwFlags = STARTF_USESTDHANDLES;
    si.StartupInfo.hStdOutput = stdout_write.get();
    si.StartupInfo.hStdError = stderr_write.get();
    si.StartupInfo.hStdInput = stdin_read.get();
    si.lpAttributeList = attr_list;

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    const BOOL ok = CreateProcessW(NULL,
                                   command_buf.data(),
                                   NULL,
                                   NULL,
                                   TRUE,
                                   CREATE_NO_WINDOW |
                                       EXTENDED_STARTUPINFO_PRESENT,
                                   NULL,
                                   NULL,
                                   &si.StartupInfo,
                                   &pi);

    DeleteProcThreadAttributeList(attr_list);
    stdout_write.reset();
    stderr_write.reset();
    stdin_read.reset();

    if (!ok) {
        const DWORD err = GetLastError();
        std::ostringstream message;
        message << "CreateProcessW failed (GetLastError=" << err << ")";
        result.error_message = message.str();
        return result;
    }

    result.spawned = true;
    UniqueHandle process(pi.hProcess);
    UniqueHandle thread(pi.hThread);
    if (!AssignProcessToJobObject(job.get(), process.get())) {
        TerminateProcess(process.get(), 1);
        WaitForSingleObject(process.get(), 2000);
        result.error_message = "AssignProcessToJobObject failed";
    }

    auto* stdout_capture = new PipeCapture{stdout_read.get(), kStdoutCap};
    auto* stderr_capture = new PipeCapture{stderr_read.get(), kStderrCap};

    HANDLE stdout_thread =
        CreateThread(NULL, 0, readerThread, stdout_capture, 0, NULL);
    HANDLE stderr_thread =
        CreateThread(NULL, 0, readerThread, stderr_capture, 0, NULL);
    if (stdout_thread == NULL || stderr_thread == NULL) {
        TerminateProcess(process.get(), 1);
        result.error_message = "CreateThread(pipe reader) failed";
    }

    if (result.error_message.empty()) {
        const DWORD waited = WaitForSingleObject(process.get(), kCliTimeoutMs);
        if (waited == WAIT_TIMEOUT) {
            result.timed_out = true;
        } else {
            DWORD code = 0;
            if (GetExitCodeProcess(process.get(), &code)) {
                result.exit_code = static_cast<int>(code);
            }
        }
    }

    job.reset();
    if (result.timed_out) {
        WaitForSingleObject(process.get(), 2000);
    }

    if (stdout_thread != NULL) {
        finishReaderThread(stdout_thread,
                           stdout_read,
                           stdout_capture,
                           result.stdout_text,
                           result.stdout_truncated,
                           result.error_message);
        stdout_capture = nullptr;
    } else {
        delete stdout_capture;
        stdout_capture = nullptr;
    }
    if (stderr_thread != NULL) {
        finishReaderThread(stderr_thread,
                           stderr_read,
                           stderr_capture,
                           result.stderr_text,
                           result.stderr_truncated,
                           result.error_message);
        stderr_capture = nullptr;
    } else {
        delete stderr_capture;
        stderr_capture = nullptr;
    }

    return result;
}

#else

long long nowMs() {
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

void setNonblocking(int fd) {
    const int flags = fcntl(fd, F_GETFL, 0);
    if (flags >= 0) {
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    }
}

void setCloseOnExec(int fd) {
    const int flags = fcntl(fd, F_GETFD, 0);
    if (flags >= 0) {
        fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
    }
}

struct FdCapture {
    int         fd = -1;
    std::string* output = nullptr;
    std::size_t cap = 0;
    bool*       truncated = nullptr;
    bool        open = false;
};

void drainFd(FdCapture& capture) {
    char buffer[8192];
    while (capture.open) {
        const ssize_t n = read(capture.fd, buffer, sizeof(buffer));
        if (n > 0) {
            const std::size_t available =
                capture.output->size() < capture.cap
                    ? capture.cap - capture.output->size()
                    : 0;
            const std::size_t copy =
                std::min<std::size_t>(available, static_cast<std::size_t>(n));
            if (copy > 0) {
                capture.output->append(buffer, copy);
            }
            if (copy < static_cast<std::size_t>(n) &&
                capture.truncated != nullptr) {
                *capture.truncated = true;
            }
            continue;
        }
        if (n == 0) {
            capture.open = false;
            break;
        }
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
            break;
        }
        capture.open = false;
    }
}

CliResult runAuraCli(const fs::path& exe, const std::vector<CliArg>& args) {
    CliResult result;
    int stdout_pipe[2];
    int stderr_pipe[2];
    if (pipe(stdout_pipe) != 0) {
        result.error_message = "pipe(stdout) failed";
        return result;
    }
    if (pipe(stderr_pipe) != 0) {
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        result.error_message = "pipe(stderr) failed";
        return result;
    }
    setCloseOnExec(stdout_pipe[0]);
    setCloseOnExec(stdout_pipe[1]);
    setCloseOnExec(stderr_pipe[0]);
    setCloseOnExec(stderr_pipe[1]);

    const std::string exe_string = exe.string();
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(exe_string.c_str()));
    for (const CliArg& arg : args) {
        argv.push_back(const_cast<char*>(arg.narrow.c_str()));
    }
    argv.push_back(nullptr);

    const pid_t pid = fork();
    if (pid < 0) {
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[0]);
        close(stderr_pipe[1]);
        result.error_message = "fork failed";
        return result;
    }

    if (pid == 0) {
        if (setsid() < 0) {
            setpgid(0, 0);
        }
        dup2(stdout_pipe[1], STDOUT_FILENO);
        dup2(stderr_pipe[1], STDERR_FILENO);
        const int dev_null = open("/dev/null", O_RDONLY | O_CLOEXEC);
        if (dev_null >= 0) {
            dup2(dev_null, STDIN_FILENO);
            close(dev_null);
        }
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[0]);
        close(stderr_pipe[1]);
        execv(exe_string.c_str(), argv.data());
        _exit(127);
    }

    result.spawned = true;
    close(stdout_pipe[1]);
    close(stderr_pipe[1]);
    setNonblocking(stdout_pipe[0]);
    setNonblocking(stderr_pipe[0]);

    FdCapture stdout_capture{stdout_pipe[0],
                             &result.stdout_text,
                             kStdoutCap,
                             &result.stdout_truncated,
                             true};
    FdCapture stderr_capture{stderr_pipe[0],
                             &result.stderr_text,
                             kStderrCap,
                             &result.stderr_truncated,
                             true};

    const long long deadline = nowMs() + kCliTimeoutMs;
    int status = 0;
    bool reaped = false;
    while (!reaped || stdout_capture.open || stderr_capture.open) {
        drainFd(stdout_capture);
        drainFd(stderr_capture);

        if (!reaped) {
            const pid_t wait_result = waitpid(pid, &status, WNOHANG);
            if (wait_result == pid) {
                reaped = true;
                if (WIFEXITED(status)) {
                    result.exit_code = WEXITSTATUS(status);
                } else if (WIFSIGNALED(status)) {
                    result.exit_code = 128 + WTERMSIG(status);
                }
            }
        }

        if (!reaped && nowMs() >= deadline) {
            if (kill(-pid, SIGKILL) != 0) {
                kill(pid, SIGKILL);
            }
            waitpid(pid, &status, 0);
            result.timed_out = true;
            reaped = true;
            result.exit_code = -1;
        }

        if ((!stdout_capture.open && !stderr_capture.open) || result.timed_out) {
            if (reaped) {
                break;
            }
        }

        pollfd fds[2];
        nfds_t nfds = 0;
        if (stdout_capture.open) {
            fds[nfds].fd = stdout_capture.fd;
            fds[nfds].events = POLLIN | POLLHUP | POLLERR;
            ++nfds;
        }
        if (stderr_capture.open) {
            fds[nfds].fd = stderr_capture.fd;
            fds[nfds].events = POLLIN | POLLHUP | POLLERR;
            ++nfds;
        }
        if (nfds == 0) {
            continue;
        }
        poll(fds, nfds, 50);
    }

    close(stdout_pipe[0]);
    close(stderr_pipe[0]);
    return result;
}

#endif

cJSON* envelopeError(const char* kind,
                     const char* code,
                     const std::string& message) {
    return aura_mcp_envelope_error(kToolSchemaVersion,
                                   kind,
                                   code,
                                   message.c_str(),
                                   kDisclosure);
}

std::string jsonStringField(const cJSON* object, const char* key) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, key);
    return cJSON_IsString(item) && item->valuestring != nullptr
               ? item->valuestring
               : "";
}

int jsonIntField(const cJSON* object, const char* key, int fallback) {
    const cJSON* item = cJSON_GetObjectItemCaseSensitive(object, key);
    return cJSON_IsNumber(item) ? item->valueint : fallback;
}

void setStringField(cJSON* object, const char* key, const std::string& value) {
    cJSON* item = cJSON_CreateString(value.c_str());
    if (item == nullptr) {
        return;
    }
    if (!cJSON_ReplaceItemInObjectCaseSensitive(object, key, item)) {
        cJSON_AddItemToObject(object, key, item);
    }
}

void setBoolField(cJSON* object, const char* key, bool value) {
    cJSON* item = cJSON_CreateBool(value ? 1 : 0);
    if (item == nullptr) {
        return;
    }
    if (!cJSON_ReplaceItemInObjectCaseSensitive(object, key, item)) {
        cJSON_AddItemToObject(object, key, item);
    }
}

void setNumberField(cJSON* object, const char* key, double value) {
    cJSON* item = cJSON_CreateNumber(value);
    if (item == nullptr) {
        return;
    }
    if (!cJSON_ReplaceItemInObjectCaseSensitive(object, key, item)) {
        cJSON_AddItemToObject(object, key, item);
    }
}

cJSON* findingToJson(const aura::safety::ProtectedExportFinding& finding) {
    cJSON* item = cJSON_CreateObject();
    if (item == nullptr) {
        return nullptr;
    }
    cJSON_AddStringToObject(item, "detector_id", finding.detector_id.c_str());
    cJSON_AddStringToObject(item, "kind", finding.kind.c_str());
    cJSON_AddNumberToObject(item, "start", static_cast<double>(finding.start));
    cJSON_AddNumberToObject(item, "end", static_cast<double>(finding.end));
    cJSON_AddNumberToObject(item, "confidence", finding.confidence);
    cJSON_AddStringToObject(item, "mask_token", finding.mask_token.c_str());
    return item;
}

void setFindingsField(
    cJSON* object,
    const std::vector<aura::safety::ProtectedExportFinding>& findings) {
    cJSON* array = cJSON_CreateArray();
    if (array == nullptr) {
        return;
    }
    for (const auto& finding : findings) {
        cJSON* item = findingToJson(finding);
        if (item != nullptr) {
            cJSON_AddItemToArray(array, item);
        }
    }
    if (!cJSON_ReplaceItemInObjectCaseSensitive(object, "findings", array)) {
        cJSON_AddItemToObject(object, "findings", array);
    }
}

cJSON* parseCliJsonOrError(const char* kind, const std::string& stdout_text) {
    cJSON* parsed =
        cJSON_ParseWithLength(stdout_text.data(), stdout_text.size());
    if (parsed == nullptr) {
        return envelopeError(kind,
                             "cli_invalid_json",
                             "aura CLI stdout was not valid JSON");
    }

    if (streq(kind, "aura_analyze")) {
        aura_mcp_normalize_analyze_cli_json(parsed);
    }

    cJSON* data = cJSON_CreateObject();
    if (data == nullptr) {
        cJSON_Delete(parsed);
        return nullptr;
    }
    if (!cJSON_AddItemToObject(data, "aura_cli", parsed)) {
        cJSON_Delete(parsed);
        cJSON_Delete(data);
        return nullptr;
    }
    cJSON* envelope = aura_mcp_envelope_success(kToolSchemaVersion,
                                                kind,
                                                data,
                                                kDisclosure);
    if (envelope == nullptr) {
        cJSON_Delete(data);
    }
    return envelope;
}

cJSON* runCliAndWrap(const char* kind, const std::vector<CliArg>& args) {
    const fs::path aura_cli = locateAuraCli();
    if (aura_cli.empty()) {
        return envelopeError(
            kind,
            "cli_not_found",
            "aura CLI executable was not found under AURA_REPO_ROOT/current working directory");
    }

    const CliResult result = runAuraCli(aura_cli, args);
    if (!result.spawned) {
        const std::string message =
            result.error_message.empty() ? "aura CLI could not be started"
                                         : result.error_message;
        return envelopeError(kind, "cli_failed", message);
    }
    if (result.timed_out) {
        return envelopeError(kind, "cli_failed", "aura CLI timed out");
    }
    if (!result.error_message.empty()) {
        return envelopeError(kind, "cli_failed", result.error_message);
    }
    if (result.stdout_truncated) {
        return envelopeError(kind,
                             "cli_output_too_large",
                             "aura CLI stdout exceeded the MCP bridge limit");
    }
    if (result.exit_code != 0) {
        std::ostringstream message;
        message << "aura CLI exited with code " << result.exit_code;
        const std::string stderr_message = trimForMessage(result.stderr_text);
        if (!stderr_message.empty()) {
            message << ": " << stderr_message;
        }
        return envelopeError(kind, "cli_failed", message.str());
    }
    return parseCliJsonOrError(kind, result.stdout_text);
}

cJSON* callProbeEngines() {
    return runCliAndWrap("aura_probe_engines",
                         {literalArg("--compact"),
                          literalArg("--probe-engines")});
}

cJSON* callBinaryTool(const char* tool_name,
                      const char* cli_command,
                      cJSON*      args_or_null) {
    if (!cJSON_IsObject(args_or_null)) {
        return envelopeError(tool_name,
                             "invalid_arguments",
                             "tool arguments must be an object");
    }

    const cJSON* binary_path =
        cJSON_GetObjectItemCaseSensitive(args_or_null, "binary_path");
    if (!cJSON_IsString(binary_path) || !nonempty(binary_path->valuestring)) {
        return envelopeError(tool_name,
                             "invalid_arguments",
                             "binary_path must be a non-empty string");
    }

    const fs::path candidate = pathFromUtf8(binary_path->valuestring);
    const AuraMcpPathDecision decision = aura_mcp_path_allowed(candidate);
    if (!decision.allowed) {
        const std::string code = decision.error_code.empty()
                                     ? "path_denied"
                                     : decision.error_code;
        const std::string message = decision.error_message.empty()
                                        ? "binary path is not allowed"
                                        : decision.error_message;
        return envelopeError(tool_name, code.c_str(), message);
    }

    std::error_code ec;
    fs::path canonical_binary = fs::canonical(candidate, ec);
    if (ec) {
        canonical_binary = pathFromUtf8(decision.canonical_path.c_str());
    }
    return runCliAndWrap(
        tool_name,
        {literalArg("--compact"),
         literalArg(cli_command),
         pathArg(canonical_binary)});
}

}  // namespace

void aura_mcp_normalize_analyze_cli_json(cJSON* cli_json) {
    if (!cJSON_IsObject(cli_json)) {
        return;
    }
    cJSON* body = cJSON_GetObjectItemCaseSensitive(cli_json, "body");
    if (!cJSON_IsObject(body)) {
        return;
    }
    cJSON* strings = cJSON_GetObjectItemCaseSensitive(body, "strings");
    if (!cJSON_IsArray(strings)) {
        return;
    }

    int fallback_id = 0;
    cJSON* row = nullptr;
    cJSON_ArrayForEach(row, strings) {
        ++fallback_id;
        if (!cJSON_IsObject(row)) {
            continue;
        }
        const cJSON* content_item =
            cJSON_GetObjectItemCaseSensitive(row, "content");
        if (!cJSON_IsString(content_item) ||
            content_item->valuestring == nullptr) {
            continue;
        }

        const std::string content = content_item->valuestring;
        const int string_id =
            jsonIntField(row, "string_id",
                         jsonIntField(row, "id", fallback_id));
        std::string source = jsonStringField(row, "source");
        if (source.empty()) {
            source = "cli.analyze.strings";
        }

        const auto record = aura::safety::buildProtectedExportRecord(
            string_id, content, source);

        cJSON_DeleteItemFromObjectCaseSensitive(row, "content");
        setNumberField(row, "string_id", static_cast<double>(record.string_id));
        setStringField(row, "protected_value", record.protected_value);
        setStringField(row, "masked_content", record.masked_content);
        setStringField(row, "source", record.source);
        setStringField(row, "raw_content", record.raw_content);
        setNumberField(row, "findings_count",
                       static_cast<double>(record.findings_count));
        setBoolField(row, "protected_only", true);
        setFindingsField(row, record.findings);
    }
}

extern "C" cJSON* aura_mcp_cli_bridge_call_json(const char* tool_name,
                                                 cJSON*      args_or_null) {
    if (streq(tool_name, "aura_probe_engines")) {
        return callProbeEngines();
    }
    if (streq(tool_name, "aura_info")) {
        return callBinaryTool("aura_info", "info", args_or_null);
    }
    if (streq(tool_name, "aura_analyze")) {
        return callBinaryTool("aura_analyze", "analyze", args_or_null);
    }
    return envelopeError("unknown",
                         "tool_not_found",
                         "MCP CLI bridge tool was not found");
}
