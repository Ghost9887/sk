#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <common.h>
#include <string.h>
#include <variant>
#include <token.h>

class Debugger {
public:
    Debugger() = default;
    static std::string value_to_string(const Value value);
    ~Debugger() = default;
};

#endif
