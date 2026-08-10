#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <vector>
#include <string>

class Scanner
{
public:
    explicit Scanner(std::string& content);
    ~Scanner() = default;

    std::vector<Token> Tokenize();
private:
    void MakeToken(TokenType type);
    void MakeToken(TokenType type, Value value);
    char Advance();
    char Peek();
    bool IsAtEnd();
    bool Match(const char expected);
    bool IsAlpha(const char c);
    bool IsNumeric(const char c);
    bool IsAlphaNumeric(const char c);
    void ParseString();
    void ParseNumber();
    void ParseIdentifier();
private:
    std::string& mContent;
    std::vector<Token> mTokens {};
    std::size_t mStart {};
    std::size_t mCurrent {};
    std::size_t mLine { 1 };
    std::size_t mColumn {};
};

#endif
