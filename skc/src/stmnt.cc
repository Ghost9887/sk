#include "stmnt.h"
#include "expr.h"
#include <format>

ExprStmnt::ExprStmnt(std::unique_ptr<Expr> expr) :
    mExpr(std::move(expr)) {}
void ExprStmnt::Accept(StmntVisitor& visitor)
{
    visitor.VisitExprStmnt(*this);
}
std::string ExprStmnt::ToString() const
{
    return std::format("ExprStmnt[{}]", mExpr->ToString());
}

PrintStmnt::PrintStmnt(std::unique_ptr<Expr> expr) :
    mExpr(std::move(expr)) {}
void PrintStmnt::Accept(StmntVisitor& visitor) 
{
    visitor.VisitPrintStmnt(*this);
}
std::string PrintStmnt::ToString() const
{
    return std::format("PrintStmnt[{}]", mExpr->ToString());
}

BlockStmnt::BlockStmnt(std::vector<std::unique_ptr<Stmnt>> stmnts) :
    mStmnts(std::move(stmnts)) {}
void BlockStmnt::Accept(StmntVisitor& visitor)
{
    visitor.VisitBlockStmnt(*this);
}
std::string BlockStmnt::ToString() const
{
    std::string res = "BlockStmnt[";
    for (std::size_t i {}; i < mStmnts.size(); ++i)
    {
        res += mStmnts[i]->ToString();
    }
    res += "]";
    return res;
}
