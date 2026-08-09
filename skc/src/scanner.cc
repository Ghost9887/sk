#include "scanner.h"

Scanner::Scanner(std::string& content) :
    mContent(content) {}

std::vector<Token> Scanner::Tokenize()
{
    while(!IsAtEnd())
    {
        mStart = mCurrent;
        char c = Advance();
        switch(c)
        {
            case '(': 
                MakeToken(TokenType::LPAREN); break;
            case ')': 
                MakeToken(TokenType::RPAREN); break;
            case '{': 
                MakeToken(TokenType::LBRACE); break;
            case '}': 
                MakeToken(TokenType::RBRACE); break;
            case '[': 
                MakeToken(TokenType::LBRACKET); break;
            case ']': 
                MakeToken(TokenType::RBRACKET); break;
            case '.':
                MakeToken(TokenType::DOT); break;
            case ',':
                MakeToken(TokenType::COMMA); break;
            case '+': 
                MakeToken(TokenType::PLUS); break;
            case '-': 
                MakeToken(TokenType::MINUS); break;
            case '*':
                MakeToken(TokenType::STAR); break;
            case '/': 
                MakeToken(TokenType::SLASH); break;
            case '%': 
                MakeToken(TokenType::PERCENT); break;
            case ';':
                MakeToken(TokenType::SEMICOLON); break;
            case '=': 
                MakeToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
            case '!': 
                MakeToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
            case '>': 
                MakeToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
            case '<':
                MakeToken(Match('=') ? TokenType::LESSER_EQUAL : TokenType::LESSER); break;
            case '\n':
                mLine++; mColumn = 0; break;
            case '"':
                ParseString(); break;
            default: 
                if (IsNumeric(c)) ParseNumber();
                else if (IsAlpha(c)) ParseIdentifier(); 
                break;
        }
    }

    return mTokens;
}

void Scanner::MakeToken(TokenType type)
{
    mTokens.emplace_back(Token(type, mLine, mColumn, 
                mContent.substr(mStart, mCurrent - mStart), std::monostate()));
}

void Scanner::MakeToken(TokenType type, Value value)
{
    mTokens.emplace_back(Token(type, mLine, mColumn, 
                mContent.substr(mStart, mCurrent - mStart), std::move(value)));
}

char Scanner::Advance()
{
    mColumn++;
    return mContent[mCurrent++];
}

char Scanner::Peek()
{
    return mContent[mCurrent];
}

bool Scanner::IsAtEnd()
{
    return mCurrent >= mContent.size();
}

bool Scanner::Match(const char expected)
{
    if (Peek() == expected)
    {
        mCurrent++;
        return true;
    }
    return false;
}

bool Scanner::IsAlpha(const char c)
{
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c<= 'Z') ||
           c == '_';   
}

bool Scanner::IsNumeric(const char c)
{
    return '0' <= c && c <= '9';
}

bool Scanner::IsAlphaNumeric(const char c)
{
    return IsAlpha(c) || IsNumeric(c);
}

void Scanner::ParseString()
{
    mStart = mCurrent;

    while(!IsAtEnd() && Peek() != '"') Advance();

    std::string value = mContent.substr(mStart, mCurrent - mStart);
    MakeToken(TokenType::STRING, std::move(value));
    Advance();
}

void Scanner::ParseNumber()
{
    bool isDouble = false;
    while(!IsAtEnd() && IsNumeric(Peek())) Advance();

    if (Peek() == '.')
    {
        isDouble = true;
        Advance();
        while(!IsAtEnd() && IsNumeric(Peek())) Advance();
    }

    if (isDouble)
    {
        double value = std::stod(mContent.substr(mStart, mCurrent - mStart));
        MakeToken(TokenType::NUMBER, value);
    }else
    {
        int value = std::stoi(mContent.substr(mStart, mCurrent - mStart));
        MakeToken(TokenType::NUMBER, value);
    }
}

void Scanner::ParseIdentifier()
{
    while (!IsAtEnd() && IsAlphaNumeric(Peek())) Advance();
    
    std::string identifier = mContent.substr(mStart, mCurrent - mStart);

    if (keywordsMap.find(identifier) != keywordsMap.end())
    {
        MakeToken(keywordsMap[identifier]);
    }else if (identifier == "pravda" || identifier == "nepravda")
    {
        if (identifier == "pravda") MakeToken(TokenType::BOOLEAN, true);
        else MakeToken(TokenType::BOOLEAN, false);
    }else if (identifier == "nic") MakeToken(TokenType::NIL);
    else MakeToken(TokenType::IDENTIFIER);
}
