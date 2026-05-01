#ifndef STMNT_H
#define STMNT_H

#include <expr.h>

class Stmnt {
public:
    virtual std::string to_string() = 0;
    virtual ~Stmnt() = default;
};

class ExpressionStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> m_expression;
public:
    ExpressionStmnt(std::shared_ptr<Expr> expression);
    std::string to_string() override;
};

class PrintStmnt : public Stmnt {
public:
    std::shared_ptr<Expr> m_expression;
public:
    PrintStmnt(std::shared_ptr<Expr> expression);
    std::string to_string() override;
};

#endif
