#include <parser.h>

Parser::Parser(std::vector<Token> tokens) :
    m_tokens(tokens) {}

std::vector<std::shared_ptr<Stmnt>> Parser::parse() {
    std::vector<std::shared_ptr<Stmnt>> statements {};
    
    while(m_ip < m_tokens.size()) {
        statements.push_back(expression());
    }

    return statements;
}

std::shared_ptr<Stmnt> Parser::expression() {
    std::shared_ptr<Stmnt> statement { std::make_shared<ExpressionStmnt>(expression_stmnt()) };
    consume(TokenType::T_SEMICOLON, "Ocakavany ';'");
    return statement;
}

std::shared_ptr<Expr> Parser::expression_stmnt() {
    return equality();
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr { comparison() };

    if (match(TokenType::T_BANG_EQUAL, TokenType::T_EQUAL_EQUAL)) {
        Token op { previous() };
        std::shared_ptr<Expr> right { comparison() };
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr { additive() };

    if (match(TokenType::T_GREATER, TokenType::T_GREATER_EQUAL, 
            TokenType::T_LESSER, TokenType::T_LESSER_EQUAL)) {
        Token op { previous() };
        std::shared_ptr<Expr> right { additive() };
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::additive() {
    std::shared_ptr<Expr> expr { factor() };

    if (match(TokenType::T_PLUS, TokenType::T_MINUS)) {
        Token op { previous() };
        std::shared_ptr<Expr> right { factor() };
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr { unary() };

    if (match(TokenType::T_STAR, TokenType::T_SLASH)) {
        Token op { previous() };
        std::shared_ptr<Expr> right { unary() };
        return std::make_shared<BinaryExpr>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::unary() {
    if (match(TokenType::T_MINUS, TokenType::T_BANG)) {
        Token op { previous() };
        std::shared_ptr<Expr> right { unary() };
        return std::make_shared<UnaryExpr>(op, right);
    }

    return primary();
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(TokenType::T_NUMBER, TokenType::T_STRING)) { 
        return std::make_shared<ValueExpr>(previous().get_value());
    }else if (match(TokenType::T_LPAREN)) {
        std::shared_ptr<Expr> expr { expression_stmnt() };
        consume(TokenType::T_RPAREN, "Ocakavany ')'");
        return std::make_shared<GroupingExpr>(expr);
    }
    
    return nullptr;
}

template<typename... TokenTypes>
bool Parser::match(TokenTypes... types) {
    for (TokenType type : {types...}) {
        if (peek().get_type() == type){ 
            advance();
            return true;
        }
    }

    return false;
}

Token &Parser::peek() {
    return m_tokens.at(m_ip);
}

Token Parser::previous() {
    return m_tokens.at(m_ip - 1);
}

void Parser::advance() {
    m_ip++;
}

void Parser::consume(TokenType type, const std::string message) {
    if (peek().get_type() == type) {
        advance();
        return;
    }

    throw ParseError(std::format("{} riadok: {}", message, peek().get_line()));
}
