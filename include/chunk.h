#ifndef CHUNK_H
#define CHUNK_H

#include <common.h>
#include <vector>
#include <cstdint>

using Byte = std::uint8_t;

enum class OpCode {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MODULO,
    OP_RETURN
};

class Chunk {
public:
    Chunk() = default;
    void write_chunk(Byte byte, int line);
    std::vector<Byte> &get_codes();
    std::vector<int> &get_lines();
    ~Chunk() = default;
private:
    std::vector<Byte> m_codes {};
    std::vector<int> m_lines {};
};

#endif
