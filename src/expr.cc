#include "expr.h"
#include <format>

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, TokenType op, std::unique_ptr<Expr> right) :
    mLeft(std::move(left)), mOp(op), mRight(std::move(right)) {}
void BinaryExpr::Accept(ExprVisitor& visitor)
{
    visitor.VisitBinaryExpr(*this);
}
std::string BinaryExpr::ToString() const
{
    return std::format("BinaryExpr[{} {} {}]", mLeft->ToString(), tokensMap[mOp], mRight->ToString());
}

UnaryExpr::UnaryExpr(TokenType op, std::unique_ptr<Expr> right) :
    mOp(op), mRight(std::move(right)) {}
void UnaryExpr::Accept(ExprVisitor& visitor)
{
    visitor.VisitUnaryExpr(*this);
}
std::string UnaryExpr::ToString() const
{
    return std::format("UnaryExpr[{} {}]", tokensMap[mOp], mRight->ToString());
}

GroupExpr::GroupExpr(std::unique_ptr<Expr> expr) :
    mExpr(std::move(expr)) {}
void GroupExpr::Accept(ExprVisitor& visitor)
{
    visitor.VisitGroupExpr(*this);
}
std::string GroupExpr::ToString() const
{
    return std::format("GroupExpr[{}]", mExpr->ToString());
}

ValueExpr::ValueExpr(Value value) :
    mValue(std::move(value)) {}
void ValueExpr::Accept(ExprVisitor& visitor)
{
    visitor.VisitValueExpr(*this);
}
std::string ValueExpr::ToString() const
{
    return std::format("ValueExpr[{}]", ValueToString(mValue));
}
