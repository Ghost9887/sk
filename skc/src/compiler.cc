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
    Evaluate(*stmnt.mExpr);
    WriteCode(OpCode::PRINT);
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
    {
        WriteCode(OpCode::STRING);
        WriteString(std::get<std::string>(expr.mValue));
    }

    else if(std::holds_alternative<int>(expr.mValue))
    {
        WriteCode(OpCode::INT);
        WriteValue<int>(std::get<int>(expr.mValue));
    }

    else if (std::holds_alternative<double>(expr.mValue))
    {
        WriteCode(OpCode::DOUBLE);
        WriteValue<double>(std::get<double>(expr.mValue));
    }

    else if (std::holds_alternative<bool>(expr.mValue))
    {
        WriteCode(OpCode::BOOLEAN);
        WriteValue<bool>(std::get<bool>(expr.mValue));
    }
    
    else WriteCode(OpCode::NIL);
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

template<typename T>
void Compiler::WriteValue(T value)
{
    mOutputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void Compiler::Evaluate(Expr& expr)
{
    expr.Accept(*this);
}

void Compiler::Execute(Stmnt& stmnt)
{
    stmnt.Accept(*this);
}
