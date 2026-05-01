#include <parser.h>

Parser::Parser(std::vector<Token> tokens) :
    m_tokens(tokens) {}

std::vector<std::shared_ptr<Stmnt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmnt>> statements {};
    return statements;
}

bool Parser::match(std::initializer_list<TokenType> tokens) {
    for (TokenType type : tokens) {
        if (peek().get_type() == type) {
            advance();
            return true;
        }
    }
    return false;
}

Token &Parser::peek() {
    return m_tokens.at(m_ip);
}

void Parser::advance() {
    m_ip++;
}

void Parser::consume(TokenType type) {
    if (peek().get_type() == type) {
        advance();
    }
}
