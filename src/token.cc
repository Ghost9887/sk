#include "token.h"
#include <format>

Token::Token(TokenType type, std::size_t line, 
        std::size_t column, std::string lexeme, Value value) :
    mType(type), mLine(line), mColumn(column), 
    mLexeme(std::move(lexeme)), mValue(std::move(value)) {}

std::string Token::ToString() const
{
    return std::format("Token[{} | {} | {} | {} | {}]", tokensMap[mType], mLine, 
            mColumn, mLexeme, ValueToString(mValue));
}

TokenType Token::GetType() const
{
    return mType;
}

std::size_t Token::GetLine() const
{
    return mLine;
}

std::size_t Token::GetColumn() const
{
    return mColumn;
}

const std::string& Token::GetLexeme() const
{
    return mLexeme;
}

const Value& Token::GetValue() const
{
    return mValue;
}
