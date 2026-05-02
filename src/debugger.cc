#include <debugger.h>

int Debugger::print_simple_instruction(const std::string instruction, int offset) {
    std::cout << std::format("[ {} ]", instruction);
    return ++offset;
}

int Debugger::print_instruction(Chunk &chunk, int offset) {
    std::vector<Byte> &codes { chunk.get_codes() };
    
    switch (static_cast<OpCode>(codes.at(offset))) {
        case OpCode::OP_RETURN:
            return print_simple_instruction("OP_RETURN", offset);
        case OpCode::OP_ADD:
            return print_simple_instruction("OP_ADD", offset);
        case OpCode::OP_SUBTRACT:
            return print_simple_instruction("OP_SUBTRACT", offset);
        case OpCode::OP_MULTIPLY:
            return print_simple_instruction("OP_MULTIPLY", offset);
        case OpCode::OP_DIVIDE:
            return print_simple_instruction("OP_DIVIDE", offset);
        default: 
            std::cout << "Uknown Byte" << std::endl;
    }
    
    return ++offset;
}

void Debugger::print_chunk(Chunk &chunk) {
    for (int offset { 0 }; offset < static_cast<int>(chunk.get_codes().size());) {
        offset = print_instruction(chunk, offset);
    }
}

std::string Debugger::value_to_string(const Value value) {
    return std::visit([](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return arg;
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(arg);
        } else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "pravda" : "nepravda";
        } else {
            return "nic";
        }
    }, value);
}
