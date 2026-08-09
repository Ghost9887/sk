#ifndef EXPR_H
#define EXPR_H

#include "token.h"
#include "value.h"
#include <memory>
#include <string>

class BinaryExpr;
class UnaryExpr;
class GroupExpr;
class ValueExpr;

class ExprVisitor
{
public:
    virtual void VisitBinaryExpr(BinaryExpr& expr) = 0;
    virtual void VisitUnaryExpr(UnaryExpr& expr) = 0;
    virtual void VisitGroupExpr(GroupExpr& expr) = 0;
    virtual void VisitValueExpr(ValueExpr& expr) = 0;
    virtual ~ExprVisitor() = default;
};

class Expr
{
public:
    virtual void Accept(ExprVisitor& visitor) = 0;
    virtual std::string ToString() const = 0;
    virtual ~Expr() = default;
};

class BinaryExpr : public Expr
{
public:
    explicit BinaryExpr(std::unique_ptr<Expr> left, TokenType op, std::unique_ptr<Expr> right);
    void Accept(ExprVisitor& visitor) override;
    std::string ToString() const override;
public:
    std::unique_ptr<Expr> mLeft;
    TokenType mOp;
    std::unique_ptr<Expr> mRight;
};

class UnaryExpr : public Expr
{
public:
    explicit UnaryExpr(TokenType op, std::unique_ptr<Expr> right);
    void Accept(ExprVisitor& visitor) override;
    std::string ToString() const override;
public:
    TokenType mOp;
    std::unique_ptr<Expr> mRight;
};

class GroupExpr : public Expr
{
public:
    explicit GroupExpr(std::unique_ptr<Expr> expr);
    void Accept(ExprVisitor& visitor) override;
    std::string ToString() const override;
public:
    std::unique_ptr<Expr> mExpr;
};

class ValueExpr : public Expr
{
public:
    explicit ValueExpr(Value value);
    void Accept(ExprVisitor& visitor) override;
    std::string ToString() const override;
public:
    Value mValue;
};

#endif
