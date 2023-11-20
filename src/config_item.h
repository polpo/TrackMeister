// SPDX-FileCopyrightText: 2023 Martin J. Fiedler <keyj@emphy.de>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include <string>
#include <functional>

#include "config.h"

struct EnumItem {
    const char* name;
    int value;
};

struct ConfigParserContext {
    std::string filename;
    int lineno;
    void invalid(const char* what, const char* s);
    inline bool checkParseResult(bool result, const char* s) {
        if (!result) { invalid("value", s); }
        return result;
    }
};

struct ConfigItem {
    bool newGroup;
    const char* name;
    const char* description;
    std::function<std::string(const Config&)> getter;
    std::function<void(ConfigParserContext&, Config&, const char*)> setter;

    static bool parseBool(bool &value, const char* s);
    static std::string formatBool(bool value);
    static bool parseInt(int &value, const char* s);
    static std::string formatInt(int value);
    static bool parseFloat(float &value, const char* s);
    static std::string formatFloat(float value);
    static bool parseEnum(int &value, const char* s, const EnumItem* items);
    static std::string formatEnum(int value, const EnumItem* items);
    static bool parseColor(uint32_t &value, const char* s);
    static std::string formatColor(uint32_t value);
};

extern const ConfigItem g_ConfigItems[];
