#ifndef COMPILER_H
#define COMPILER_H

#include <memory>
#include <vector>
#include <fstream>
#include "stmnt.h"
#include "expr.h"

enum class OpCode : std::uint8_t
{
    STRING,
    INT,
    DOUBLE,
    BOOLEAN,
    NIL,
    RETURN,
    PRINT,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULO,
    NEW_ENV,
    DELETE_ENV
};

class Compiler : public StmntVisitor, public ExprVisitor 
{
public:
    Compiler(std::vector<std::unique_ptr<Stmnt>>& statements);
    ~Compiler() = default;

    void Compile();
    
    void VisitExprStmnt(ExprStmnt& stmnt) override;
    void VisitBlockStmnt(BlockStmnt& stmnt) override;
    void VisitPrintStmnt(PrintStmnt& stmnt) override;

    void VisitBinaryExpr(BinaryExpr& expr) override;
    void VisitUnaryExpr(UnaryExpr& expr) override;
    void VisitGroupExpr(GroupExpr& expr) override;
    void VisitValueExpr(ValueExpr& expr) override;
private:
    void WriteCode(OpCode code);
    void WriteString(const std::string& str);
    void Evaluate(Expr& expr);
    void Execute(Stmnt& stmnt);
private:
    std::vector<std::unique_ptr<Stmnt>>& mStatements;
    std::ofstream mOutputFile;
};

#endif
