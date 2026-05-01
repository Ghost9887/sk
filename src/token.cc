#include <token.h>

Token::Token(const TokenType type, const int line,  const std::string lexeme, const Value value) :
    m_type(type), m_line(line), m_lexeme(lexeme), m_value(value) {}

std::string Token::to_string() const {
    return "[" + token_map.at(m_type) + " : '" + m_lexeme + "' : " + std::to_string(m_line) + " : " + value_to_string(m_value) + "]";  
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

std::string Token::value_to_string(Value value) const{
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
