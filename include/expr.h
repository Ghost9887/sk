#ifndef EXPR_H
#define EXPR_H

#include <debugger.h>
#include <token.h>
#include <memory>
#include <string>

class Expr {
public:
    virtual std::string to_string() = 0;
    virtual ~Expr() = default;
};

class ValueExpr : public Expr {
public:
    Value m_value;
public:
    ValueExpr(Value value);
    std::string to_string() override;
};

class BinaryExpr : public Expr {
public:
    std::shared_ptr<Expr> m_left;
    Token m_op;
    std::shared_ptr<Expr> m_right;
public:
    BinaryExpr(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
};

class UnaryExpr : public Expr {
public:
    Token m_op;
    std::shared_ptr<Expr> m_right;
public:
    UnaryExpr(Token op, std::shared_ptr<Expr> right);
    std::string to_string() override;
};

class GroupingExpr : public Expr {
public:
    std::shared_ptr<Expr> m_expression;
public:
    GroupingExpr(std::shared_ptr<Expr> expression);
    std::string to_string() override;
};

#endif
