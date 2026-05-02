#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <common.h>
#include <string.h>
#include <variant>
#include <token.h>
#include <chunk.h>

class Debugger {
public:
    Debugger() = default;
    static std::string value_to_string(const Value value);
    static int print_simple_instruction(const std::string instruction, int offset);
    static int print_instruction(Chunk &chunk, int offset);
    static void print_chunk(Chunk &chunk);
    ~Debugger() = default;
};

#endif
