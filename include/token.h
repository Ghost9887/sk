#ifndef TOKEN_H
#define TOKEN_H

#include <common.h>
#include <string>
#include <unordered_map>
#include <variant>

enum class TokenType {
    T_PLUS, T_MINUS, T_STAR, T_SLASH,
    T_PERCENT, T_DOT, T_COMMA, T_LPAREN, 
    T_RPAREN, T_LBRACE, T_RBRACE, T_SEMICOLON, 

    T_GREATER, T_GREATER_EQUAL, T_BANG, T_BANG_EQUAL,
    T_LESSER, T_LESSER_EQUAL, T_EQUAL, T_EQUAL_EQUAL,
    T_AND, T_OR, 

    T_VYTLAC, T_IDENTIFIER, T_NUMBER, T_STRING, T_AK,
    T_ALEBO, T_FUNK, T_TRIEDA, T_SUPER, T_INAK, T_AK_INAK,
    T_A
};

static inline std::unordered_map<TokenType, std::string> token_map {
    {TokenType::T_PLUS, "T_Plus"}, {TokenType::T_MINUS, "T_Minus"},
    {TokenType::T_STAR, "T_Star"}, {TokenType::T_SLASH, "T_Slash"},
    {TokenType::T_PERCENT, "T_Percent"}, {TokenType::T_DOT, "T_Dot"}, 
    {TokenType::T_COMMA, "T_Comma"}, {TokenType::T_LPAREN, "T_LParen"}, 
    {TokenType::T_RPAREN, "T_RParen"}, {TokenType::T_LBRACE, "T_LBrace"}, 
    {TokenType::T_RBRACE, "T_RBrace"}, {TokenType::T_SEMICOLON, "T_Semicolon"}, 
    {TokenType::T_GREATER, "T_Greater"}, {TokenType::T_GREATER_EQUAL, "T_Greater_Equal"}, 
    {TokenType::T_LESSER, "T_Lesser"}, {TokenType::T_LESSER_EQUAL, "T_Lesser_Equal"}, 
    {TokenType::T_EQUAL, "T_Equal"}, {TokenType::T_EQUAL_EQUAL, "T_Equal_Equal"},
    {TokenType::T_BANG, "T_Bang"}, {TokenType::T_BANG_EQUAL, "T_Bang_Equal"},
    {TokenType::T_AND, "T_And"}, {TokenType::T_OR, "T_Or"}, 
    {TokenType::T_VYTLAC, "T_Vytlac"}, {TokenType::T_IDENTIFIER, "T_Identifier"}, 
    {TokenType::T_NUMBER, "T_Number"}, {TokenType::T_AK, "T_Ak"}, 
    {TokenType::T_STRING, "T_String"}, {TokenType::T_ALEBO, "T_Alebo"}, 
    {TokenType::T_FUNK, "T_Funk"}, {TokenType::T_TRIEDA, "T_Trieda"}, 
    {TokenType::T_SUPER, "T_Super"}, {TokenType::T_INAK, "T_INAK"}, 
    {TokenType::T_AK_INAK, "T_Ak_Inak"}, {TokenType::T_A, "T_AA"}
};

static inline std::unordered_map<std::string, TokenType> keywords_map {
    {"vytlac", TokenType::T_VYTLAC}, {"ak", TokenType::T_AK}, {"alebo", TokenType::T_ALEBO}, {"funk", TokenType::T_FUNK},
    {"trieda", TokenType::T_TRIEDA}, {"super", TokenType::T_SUPER}, {"inak", TokenType::T_INAK}, {"aa", TokenType::T_A},
    {"akinak", TokenType::T_AK_INAK}
};

using Value = std::variant<std::monostate, double, std::string, bool>;

class Token {
public:
    Token(
        const TokenType type, 
        const int line, 
        const std::string lexeme,
        const Value value
    );
    std::string to_string() const;
    TokenType get_type() const;
    int get_line() const;
    std::string get_lexeme() const;
    Value get_value() const;
    ~Token() = default;
public:
    bool operator==(const Token& other) const {
        return m_type == other.get_type() &&
               m_line == other.get_line() &&
               m_lexeme == other.get_lexeme();
    }
private:
    const TokenType m_type;
    const int m_line;
    const std::string m_lexeme;
    const Value m_value;
}; 

inline std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << t.to_string();
    return os;
}

#endif
