#include "compiler.h"

Compiler::Compiler(std::vector<std::unique_ptr<Stmnt>>& statements) :
    mStatements(statements) 
{
    mOutputFile = std::ofstream("output.skc");
}

void Compiler::Compile() 
{
    for (std::size_t i {}; i < mStatements.size(); ++i)
    {
        Execute(*mStatements[i]);
    }
}
    
void Compiler::VisitExprStmnt(ExprStmnt& stmnt) 
{
    Evaluate(*stmnt.mExpr);
}

void Compiler::VisitBlockStmnt([[maybe_unused]]BlockStmnt& stmnt) 
{}

void Compiler::VisitPrintStmnt(PrintStmnt& stmnt) 
{
    WriteCode(OpCode::PRINT);
    Evaluate(*stmnt.mExpr);
}

void Compiler::VisitBinaryExpr([[maybe_unused]]BinaryExpr& expr) 
{}

void Compiler::VisitUnaryExpr([[maybe_unused]]UnaryExpr& expr) 
{}

void Compiler::VisitGroupExpr(GroupExpr& expr) 
{
    Evaluate(*expr.mExpr);
}

void Compiler::VisitValueExpr(ValueExpr& expr) 
{
    if (std::holds_alternative<std::string>(expr.mValue))
            WriteString(std::get<std::string>(expr.mValue));
}

void Compiler::WriteCode(OpCode code)
{
    char byte = static_cast<char>(code);
    mOutputFile.write(&byte, sizeof(byte));
}

void Compiler::WriteString(const std::string& str)
{
    std::uint32_t len = str.size();   
    mOutputFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
    mOutputFile.write(str.c_str(), len);
}

void Compiler::Evaluate(Expr& expr)
{
    expr.Accept(*this);
}

void Compiler::Execute(Stmnt& stmnt)
{
    stmnt.Accept(*this);
}
