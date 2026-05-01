#ifndef PARSER_H
#define PARSER_H

#include <common.h>
#include <token.h>
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
    bool match(std::initializer_list<TokenType> tokens);
    Token &peek();
    void advance();
    void consume(TokenType type);
};

#endif
