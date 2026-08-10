#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <string>
#include <memory>
#include <vector>
#include <initializer_list>
#include <optional>

class Stmnt;
class Expr;

class Parser
{
public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser() = default;
    
    std::vector<std::unique_ptr<Stmnt>> Parse();
private:
    std::unique_ptr<Stmnt> Statement();
    std::unique_ptr<Stmnt> PrintStatement();
    std::unique_ptr<Stmnt> BlockStatement();
    std::unique_ptr<Stmnt> ExprStatement();
    std::unique_ptr<Expr> Expression();
    std::unique_ptr<Expr> Equality();
    std::unique_ptr<Expr> Comparison();
    std::unique_ptr<Expr> Term();
    std::unique_ptr<Expr> Factor();
    std::unique_ptr<Expr> Unary();
    std::unique_ptr<Expr> Primary();

    void Advance();
    std::optional<std::reference_wrapper<Token>> Peek();
    Token& Previous();
    bool Match(std::initializer_list<TokenType> types);
    void Consume(TokenType type, const std::string& message);
    void Synchronize();
    [[noreturn]]
    void Error(const std::string message);
private:
    std::vector<Token> mTokens;
    std::size_t mIp;
};

#endif
