#ifndef PARSER_H
#define PARSER_H

#include <common.h>
#include <token.h>
#include <parse_error.h>
#include <vector>
#include <stmnt.h>

class Parser {
public:
    Parser(std::vector<Token> tokens);
    std::vector<std::shared_ptr<Stmnt>> parse();
private:
    std::vector<Token> m_tokens;
    std::size_t m_ip { 0 };
private:
    std::shared_ptr<Stmnt> expression();
    std::shared_ptr<Expr> expression_stmnt();
    std::shared_ptr<Expr> equality(); 
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> additive();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();

    template<typename... TokenTypes>
    bool match(TokenTypes... types);

    Token &peek();
    Token previous();
    void advance();
    void consume(TokenType type, const std::string message);
};

#endif
