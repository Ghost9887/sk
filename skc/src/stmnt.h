#ifndef STMNT_H
#define STMNT_H

#include <memory>
#include <string>
#include <vector>

class Expr;

class ExprStmnt;
class PrintStmnt;
class BlockStmnt;

class StmntVisitor
{
public:
    virtual void VisitExprStmnt(ExprStmnt& stmnt) = 0;
    virtual void VisitBlockStmnt(BlockStmnt& stmnt) = 0;
    virtual void VisitPrintStmnt(PrintStmnt& stmnt) = 0;
    virtual ~StmntVisitor() = default;
};

class Stmnt
{
public:
    virtual void Accept(StmntVisitor& visitor) = 0;
    virtual std::string ToString() const = 0;
    virtual ~Stmnt() = default;
};

class ExprStmnt : public Stmnt
{
public:   
    explicit ExprStmnt(std::unique_ptr<Expr> expr);
    void Accept(StmntVisitor& visitor) override;
    std::string ToString() const override;
public:
    std::unique_ptr<Expr> mExpr;
};

class PrintStmnt : public Stmnt
{
public:
    explicit PrintStmnt(std::unique_ptr<Expr> expr);
    void Accept(StmntVisitor& visitor) override;
    std::string ToString() const override;
public:
    std::unique_ptr<Expr> mExpr;
};

class BlockStmnt : public Stmnt
{
public:
    explicit BlockStmnt(std::vector<std::unique_ptr<Stmnt>> stmnt);
    void Accept(StmntVisitor& visitor) override;
    std::string ToString() const override;
public:
    std::vector<std::unique_ptr<Stmnt>> mStmnts;
};

#endif
