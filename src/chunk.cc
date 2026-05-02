#include <chunk.h>

void Chunk::write_chunk(Byte byte, int line) {
    m_codes.push_back(byte);
    if (m_lines.empty()) {
        m_lines.push_back(1);
        m_lines.push_back(line);
    }else {
        if (m_lines.back() == line) {
            m_lines.at(m_lines.size() - 2)++;
        }
    }
}

std::vector<Byte> &Chunk::get_codes() {
    return m_codes;
}

std::vector<int> &Chunk::get_lines() {
    return m_lines;
}
