#include <token.h>

Token::Token(const TokenType type, const int line,  const std::string lexeme, const Value value) :
    m_type(type), m_line(line), m_lexeme(lexeme), m_value(value) {}

std::string Token::to_string() const {
    return "[" + token_map.at(m_type) + " : '" + m_lexeme + "' : " + std::to_string(m_line) + "]";  
}

TokenType Token::get_type() const {
    return m_type;
}

int Token::get_line() const {
    return m_line;
}

std::string Token::get_lexeme() const {
    return m_lexeme;
}

Value Token::get_value() const {
    return m_value;
}
