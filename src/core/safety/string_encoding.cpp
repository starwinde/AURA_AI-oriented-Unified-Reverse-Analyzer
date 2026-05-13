// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "aura/safety/string_encoding.h"

#include <cctype>
#include <cstdio>
#include <string>

namespace aura::safety {

namespace {

bool isPrintableAsciiByte(unsigned char ch) {
    return (ch >= 0x20 && ch <= 0x7e) || ch == '\t' || ch == '\n' ||
           ch == '\r';
}

bool appendUtf8Codepoint(const std::string& bytes, std::size_t* pos,
                         std::string* out, bool* sawMultibyte) {
    const unsigned char ch = static_cast<unsigned char>(bytes[*pos]);
    if (ch < 0x80) {
        if (!isPrintableAsciiByte(ch)) return false;
        out->push_back(static_cast<char>(ch));
        ++(*pos);
        return true;
    }

    int need = 0;
    if ((ch & 0xe0) == 0xc0) need = 2;
    else if ((ch & 0xf0) == 0xe0) need = 3;
    else if ((ch & 0xf8) == 0xf0) need = 4;
    else return false;

    if (*pos + static_cast<std::size_t>(need) > bytes.size()) return false;
    for (int i = 1; i < need; ++i) {
        const unsigned char cc =
            static_cast<unsigned char>(bytes[*pos + static_cast<std::size_t>(i)]);
        if ((cc & 0xc0) != 0x80) return false;
    }
    out->append(bytes.substr(*pos, static_cast<std::size_t>(need)));
    *pos += static_cast<std::size_t>(need);
    *sawMultibyte = true;
    return true;
}

bool decodeUtf8(const std::string& bytes, std::string* out,
                bool* sawMultibyte) {
    out->clear();
    *sawMultibyte = false;
    for (std::size_t pos = 0; pos < bytes.size();) {
        if (!appendUtf8Codepoint(bytes, &pos, out, sawMultibyte))
            return false;
    }
    return true;
}

bool looksUtf16(const std::string& bytes, bool littleEndian, std::string* out) {
    if (bytes.size() < 4 || (bytes.size() % 2) != 0) return false;
    out->clear();
    std::size_t printable = 0;
    std::size_t total = 0;
    for (std::size_t i = 0; i + 1 < bytes.size(); i += 2) {
        const unsigned char lo = static_cast<unsigned char>(bytes[i]);
        const unsigned char hi = static_cast<unsigned char>(bytes[i + 1]);
        const unsigned char ascii = littleEndian ? lo : hi;
        const unsigned char zero = littleEndian ? hi : lo;
        ++total;
        if (zero != 0) return false;
        if (!isPrintableAsciiByte(ascii)) return false;
        out->push_back(static_cast<char>(ascii));
        ++printable;
    }
    return total > 0 && printable == total;
}

std::string escapedPreview(const std::string& bytes) {
    std::string out;
    char buf[5] = {};
    for (const unsigned char ch : bytes) {
        if (isPrintableAsciiByte(ch) && ch != '\\' && ch != '"') {
            out.push_back(static_cast<char>(ch));
            continue;
        }
        std::snprintf(buf, sizeof(buf), "\\x%02X", ch);
        out += buf;
    }
    return out;
}

std::string escapeLiteralText(const std::string& text) {
    std::string out;
    for (const char ch : text) {
        switch (ch) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default: out.push_back(ch); break;
        }
    }
    return out;
}

}  // namespace

DetectedStringEncoding detectStringEncoding(const std::string& bytes) {
    DetectedStringEncoding out;
    if (bytes.empty()) {
        out.label = "ascii";
        out.confidence = 1.0;
        out.display.clear();
        return out;
    }

    std::string decoded;
    if (looksUtf16(bytes, true, &decoded)) {
        out.label = "utf16le";
        out.confidence = 0.95;
        out.display = decoded;
        return out;
    }
    if (looksUtf16(bytes, false, &decoded)) {
        out.label = "utf16be";
        out.confidence = 0.95;
        out.display = decoded;
        return out;
    }

    bool sawMultibyte = false;
    if (decodeUtf8(bytes, &decoded, &sawMultibyte)) {
        out.label = sawMultibyte ? "utf8" : "ascii";
        out.confidence = sawMultibyte ? 0.98 : 1.0;
        out.display = decoded;
        return out;
    }

    out.label = "unknown";
    out.confidence = 0.20;
    out.display = escapedPreview(bytes);
    out.lossy = true;
    return out;
}

std::string displayLiteralForEncoding(const DetectedStringEncoding& encoding) {
    const std::string escaped = escapeLiteralText(encoding.display);
    if (encoding.label == "utf8") return "u8\"" + escaped + "\"";
    if (encoding.label == "utf16le" || encoding.label == "utf16be")
        return "L\"" + escaped + "\"";
    if (encoding.label == "unknown") return "\"<bytes:" + escaped + ">\"";
    return "\"" + escaped + "\"";
}

}  // namespace aura::safety
