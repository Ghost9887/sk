#include "parser.h"
#include "parse_error.h"
#include "stmnt.h"
#include "expr.h"

Parser::Parser(std::vector<Token> tokens) :
    mTokens(std::move(tokens)), mIp(0) {}

std::vector<std::unique_ptr<Stmnt>> Parser::Parse()
{
    std::vector<std::unique_ptr<Stmnt>> statements {};

    while(mIp < mTokens.size())
    {
        try {
            statements.push_back(Statement());
        }catch (const ParseError& e)
        {
            e.Log();
            Synchronize();
        }
    }

    return statements;
}

std::unique_ptr<Stmnt> Parser::Statement()
{
    if (Match({TokenType::PRINT})) return PrintStatement();
    else if (Match({TokenType::LBRACE})) return BlockStatement();

    return ExprStatement();
}

std::unique_ptr<Stmnt> Parser::PrintStatement()
{
    Consume(TokenType::LPAREN, "Ocakavany '('.");
    std::unique_ptr<Expr> expr = Expression();
    Consume(TokenType::RPAREN, "Ocakavany ')'.");
    Consume(TokenType::SEMICOLON, "Ocakavany ';'.");
    return std::make_unique<PrintStmnt>(std::move(expr));
}

std::unique_ptr<Stmnt> Parser::BlockStatement()
{
    std::vector<std::unique_ptr<Stmnt>> stmnts {};
    while (!Match({TokenType::RBRACE}))
    {
        stmnts.push_back(Statement());
    }
    return std::make_unique<BlockStmnt>(std::move(stmnts));
}

std::unique_ptr<Stmnt> Parser::ExprStatement()
{
    std::unique_ptr<Expr> expr = Expression();
    Consume(TokenType::SEMICOLON, "Ocakavany ';'.");
    return std::make_unique<ExprStmnt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::Expression()
{
    return Equality();
}

std::unique_ptr<Expr> Parser::Equality()
{
    std::unique_ptr<Expr> expr = Comparison();

    while (Match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL}))
    {
        TokenType op = Previous().GetType();
        std::unique_ptr<Expr> right = Comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Comparison()
{
    std::unique_ptr<Expr> expr = Term();

    while (Match({TokenType::GREATER, TokenType::GREATER_EQUAL, 
                TokenType::LESSER, TokenType::LESSER_EQUAL}))
    {
        TokenType op = Previous().GetType();
        std::unique_ptr<Expr> right = Term();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Term()
{
    std::unique_ptr<Expr> expr = Factor();

    while (Match({TokenType::MINUS, TokenType::PLUS}))
    {
        TokenType op = Previous().GetType();
        std::unique_ptr<Expr> right = Factor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Factor()
{
    std::unique_ptr<Expr> expr = Unary();

    while (Match({TokenType::SLASH, TokenType::STAR, TokenType::PERCENT}))
    {
        TokenType op = Previous().GetType();
        std::unique_ptr<Expr> right = Unary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::Unary()
{
    if (Match({TokenType::MINUS, TokenType::BANG}))
    {
        TokenType op = Previous().GetType();
        std::unique_ptr<Expr> right = Unary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }

    return Primary();
}

std::unique_ptr<Expr> Parser::Primary()
{
    if (Match({TokenType::BOOLEAN, TokenType::STRING, TokenType::NUMBER}))
        return std::make_unique<ValueExpr>(Previous().GetValue());
    if (Match({TokenType::LPAREN}))
    {
        std::unique_ptr<Expr> expr = Expression();
        Consume(TokenType::RPAREN, "Ocakavany ')'.");
        return std::make_unique<GroupExpr>(std::move(expr));
    }

    Error("Ocakavany primarny vyraz.");
}

void Parser::Advance()
{
    mIp++;
}

Token& Parser::Previous()
{
    return mTokens[mIp - 1];
}

std::optional<std::reference_wrapper<Token>> Parser::Peek()
{
    if (mIp < mTokens.size()) return mTokens[mIp];
    else return std::nullopt;
}

bool Parser::Match(std::initializer_list<TokenType> types)
{
    for (auto& t : types)
    {
        if (Peek().has_value()) {
            if (Peek().value().get().GetType() == t) 
            {
                Advance();
                return true;
            }
        }
    }
    return false;
}

void Parser::Consume(TokenType type, const std::string& message)
{
    if (!Match({type})) Error(message); 
}

void Parser::Synchronize()
{
    Advance();

    while (mIp < mTokens.size())
    {
        if (Previous().GetType() == TokenType::SEMICOLON) return;

        switch (Peek().value().get().GetType())
        {
            case TokenType::PRINT:
            case TokenType::IF:
            case TokenType::FOR:
            case TokenType::WHILE:
            case TokenType::CLASS:
            case TokenType::FUNC:
            case TokenType::LET:
            case TokenType::RETURN:
                return;
            default: break;
        }
        Advance();
    }
}

[[noreturn]]
void Parser::Error(const std::string message)
{
    throw ParseError(std::move(message), &Previous());
}
