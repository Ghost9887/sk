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
    std::shared_ptr<ValueExpr> m_left;
    Token m_op;
    std::shared_ptr<ValueExpr> m_right;
public:
    BinaryExpr(std::shared_ptr<ValueExpr> left, Token op, std::shared_ptr<ValueExpr> right);
    std::string to_string() override;
};

#endif
