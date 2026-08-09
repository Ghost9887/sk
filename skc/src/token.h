#ifndef TOKEN_H
#define TOKEN_H

#include "value.h"
#include <unordered_map>
#include <string>

enum class TokenType
{
    LPAREN, RPAREN, LBRACE, RBRACE,
    LBRACKET, RBRACKET, DOT, COMMA,
    PLUS, MINUS, SLASH, PERCENT, STAR,
    SEMICOLON, EQUAL, BANG, GREATER, LESSER,

    EQUAL_EQUAL, BANG_EQUAL, GREATER_EQUAL, 
    LESSER_EQUAL,

    IDENTIFIER, IF, ELSE, WHILE, FOR, FUNC, PRINT,
    STRING, NUMBER, BOOLEAN, NIL, CLASS, LET, RETURN 
};

inline static std::unordered_map<TokenType, std::string> tokensMap = 
{
    {TokenType::LPAREN, "LParen"}, {TokenType::RPAREN, "RParen"},
    {TokenType::LBRACE, "LBrace"}, {TokenType::RBRACE, "RBrace"},
    {TokenType::LBRACKET, "LBracket"}, {TokenType::RBRACKET, "RBracket"},
    {TokenType::DOT, "Dot"}, {TokenType::COMMA, "Comma"},
    {TokenType::PLUS, "Plus"}, {TokenType::MINUS, "Minus"},
    {TokenType::SLASH, "Slash"}, {TokenType::PERCENT, "Percent"},
    {TokenType::STAR, "Star"}, {TokenType::SEMICOLON, "Semicolon"},
    {TokenType::EQUAL, "Equal"}, {TokenType::BANG, "Bang"}, 
    {TokenType::GREATER, "Greater"}, {TokenType::LESSER, "Lesser"}, 

    {TokenType::EQUAL_EQUAL, "EqualEqual"}, {TokenType::BANG_EQUAL, "BangEqual"},
    {TokenType::GREATER_EQUAL, "GreaterEqual"}, {TokenType::LESSER_EQUAL, "LesserEqual"},

    {TokenType::IDENTIFIER, "Identifier"}, {TokenType::PRINT, "Print"},
    {TokenType::IF, "If"}, {TokenType::ELSE, "Else"},
    {TokenType::WHILE, "While"}, {TokenType::FOR, "For"},
    {TokenType::FUNC, "Func"}, {TokenType::STRING, "String"},
    {TokenType::NUMBER, "Number"}, {TokenType::BOOLEAN, "Boolean"},
    {TokenType::NIL, "Nil"}, {TokenType::CLASS, "Class"}, 
    {TokenType::LET, "Let"}, {TokenType::RETURN, "Return"}
};

inline static std::unordered_map<std::string, TokenType> keywordsMap = 
{
    {"ak", TokenType::IF}, {"inak", TokenType::ELSE},
    {"pokial", TokenType::WHILE}, {"pre", TokenType::FOR},
    {"vytlac", TokenType::PRINT}, {"funk", TokenType::FUNC}, 
    {"trieda", TokenType::CLASS}, {"prem", TokenType::LET},
    {"vratit", TokenType::RETURN}, {"nic", TokenType::NIL}
};

class Token
{
public:
    Token(TokenType type, std::size_t line, std::size_t column, 
            std::string lexeme, Value value);
    ~Token() = default;
    
    std::string ToString() const;
    TokenType GetType() const;
    std::size_t GetLine() const;
    std::size_t GetColumn() const;
    const std::string& GetLexeme() const;
    const Value& GetValue() const;

    bool operator==(const Token& other) const
    {
        return  mType == other.GetType() &&
                mValue == other.GetValue();
    }
private:
    TokenType mType;
    std::size_t mLine;
    std::size_t mColumn;
    std::string mLexeme;
    Value mValue;
};

#endif
