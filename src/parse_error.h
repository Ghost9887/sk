#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <string>
#include <stdexcept>
#include "sk.h"

class ParseError : public std::runtime_error
{
public:
    ParseError(std::string message, const Token* token)
        : std::runtime_error(message), mMessage(std::move(message)), mToken(token) {}

    const char* what() const noexcept override {
        return mMessage.c_str();
    }

    void Log() const {
        Sk::GetInstance().Error(mMessage, mToken);
    }

private:
    std::string mMessage;
    const Token* mToken;
};

#endif

