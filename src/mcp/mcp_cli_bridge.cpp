#include "mcp_cli_bridge.h"

#include "aura/mcp/mcp_envelope.h"
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

#ifdef _WIN32

bool needsWindowsQuoting(const std::string& arg) {
    if (arg.empty()) {
        return true;
    }
    for (const char ch : arg) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' ||
            ch == '"') {
            return true;
        }
    }
    return false;
}

std::string quoteWindowsArg(const std::string& arg) {
    if (!needsWindowsQuoting(arg)) {
        return arg;
    }

    std::string quoted = "\"";
    std::size_t backslashes = 0;
    for (const char ch : arg) {
        if (ch == '\\') {
            ++backslashes;
            continue;
        }
        if (ch == '"') {
            quoted.append(backslashes * 2 + 1, '\\');
            quoted += '"';
            backslashes = 0;
            continue;
        }
        quoted.append(backslashes, '\\');
        backslashes = 0;
        quoted += ch;
    }
    quoted.append(backslashes * 2, '\\');
    quoted += '"';
    return quoted;
}

std::string buildCommandLine(const fs::path& exe,
                             const std::vector<std::string>& args) {
    std::string command = quoteWindowsArg(exe.string());
    for (const std::string& arg : args) {
        command += ' ';
        command += quoteWindowsArg(arg);
    }
    return command;
}

struct PipeCapture {
    HANDLE      handle = NULL;
    std::string* output = nullptr;
    std::size_t cap = 0;
    bool*       truncated = nullptr;
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
            capture->output->size() < capture->cap
                ? capture->cap - capture->output->size()
                : 0;
        const std::size_t copy =
            std::min<std::size_t>(available, static_cast<std::size_t>(read));
        if (copy > 0) {
            capture->output->append(buffer, copy);
        }
        if (copy < static_cast<std::size_t>(read) &&
            capture->truncated != nullptr) {
            *capture->truncated = true;
        }
    }
    return 0;
}

CliResult runAuraCli(const fs::path& exe, const std::vector<std::string>& args) {
    CliResult result;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    HANDLE stdout_read = NULL;
    HANDLE stdout_write = NULL;
    HANDLE stderr_read = NULL;
    HANDLE stderr_write = NULL;

    if (!CreatePipe(&stdout_read, &stdout_write, &sa, 0)) {
        result.error_message = "CreatePipe(stdout) failed";
        return result;
    }
    SetHandleInformation(stdout_read, HANDLE_FLAG_INHERIT, 0);

    if (!CreatePipe(&stderr_read, &stderr_write, &sa, 0)) {
        CloseHandle(stdout_read);
        CloseHandle(stdout_write);
        result.error_message = "CreatePipe(stderr) failed";
        return result;
    }
    SetHandleInformation(stderr_read, HANDLE_FLAG_INHERIT, 0);

    std::string command = buildCommandLine(exe, args);
    std::vector<char> command_buf(command.begin(), command.end());
    command_buf.push_back('\0');

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = stdout_write;
    si.hStdError = stderr_write;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    const BOOL ok = CreateProcessA(NULL,
                                   command_buf.data(),
                                   NULL,
                                   NULL,
                                   TRUE,
                                   CREATE_NO_WINDOW,
                                   NULL,
                                   NULL,
                                   &si,
                                   &pi);

    CloseHandle(stdout_write);
    CloseHandle(stderr_write);

    if (!ok) {
        const DWORD err = GetLastError();
        std::ostringstream message;
        message << "CreateProcess failed (GetLastError=" << err << ")";
        result.error_message = message.str();
        CloseHandle(stdout_read);
        CloseHandle(stderr_read);
        return result;
    }

    result.spawned = true;
    PipeCapture stdout_capture{stdout_read,
                               &result.stdout_text,
                               kStdoutCap,
                               &result.stdout_truncated};
    PipeCapture stderr_capture{stderr_read,
                               &result.stderr_text,
                               kStderrCap,
                               &result.stderr_truncated};

    HANDLE stdout_thread =
        CreateThread(NULL, 0, readerThread, &stdout_capture, 0, NULL);
    HANDLE stderr_thread =
        CreateThread(NULL, 0, readerThread, &stderr_capture, 0, NULL);
    if (stdout_thread == NULL || stderr_thread == NULL) {
        TerminateProcess(pi.hProcess, 1);
        result.error_message = "CreateThread(pipe reader) failed";
    }

    const DWORD waited = WaitForSingleObject(pi.hProcess, kCliTimeoutMs);
    if (waited == WAIT_TIMEOUT) {
        TerminateProcess(pi.hProcess, 1);
        result.timed_out = true;
    } else {
        DWORD code = 0;
        if (GetExitCodeProcess(pi.hProcess, &code)) {
            result.exit_code = static_cast<int>(code);
        }
    }

    if (stdout_thread != NULL) {
        WaitForSingleObject(stdout_thread, INFINITE);
        CloseHandle(stdout_thread);
    }
    if (stderr_thread != NULL) {
        WaitForSingleObject(stderr_thread, INFINITE);
        CloseHandle(stderr_thread);
    }

    CloseHandle(stdout_read);
    CloseHandle(stderr_read);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
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

CliResult runAuraCli(const fs::path& exe, const std::vector<std::string>& args) {
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

    const std::string exe_string = exe.string();
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(exe_string.c_str()));
    for (const std::string& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
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
        dup2(stdout_pipe[1], STDOUT_FILENO);
        dup2(stderr_pipe[1], STDERR_FILENO);
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
            kill(pid, SIGKILL);
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

cJSON* parseCliJsonOrError(const char* kind, const std::string& stdout_text) {
    cJSON* parsed =
        cJSON_ParseWithLength(stdout_text.data(), stdout_text.size());
    if (parsed == nullptr) {
        return envelopeError(kind,
                             "cli_invalid_json",
                             "aura CLI stdout was not valid JSON");
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
    return aura_mcp_envelope_success(kToolSchemaVersion,
                                     kind,
                                     data,
                                     kDisclosure);
}

cJSON* runCliAndWrap(const char* kind, const std::vector<std::string>& args) {
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
    return runCliAndWrap("aura_probe_engines", {"--compact", "--probe-engines"});
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

    const AuraMcpPathDecision decision =
        aura_mcp_path_allowed(pathFromUtf8(binary_path->valuestring));
    if (!decision.allowed) {
        const std::string code = decision.error_code.empty()
                                     ? "path_denied"
                                     : decision.error_code;
        const std::string message = decision.error_message.empty()
                                        ? "binary path is not allowed"
                                        : decision.error_message;
        return envelopeError(tool_name, code.c_str(), message);
    }

    const std::string canonical_binary = decision.canonical_path;
    return runCliAndWrap(
        tool_name,
        {"--compact", cli_command, canonical_binary});
}

}  // namespace

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
