#include <stmnt.h>

ExpressionStmnt::ExpressionStmnt(std::shared_ptr<Expr> expression) :
    m_expression(expression) {}
std::string ExpressionStmnt::to_string() {
    return std::format("{{ExpressionStmnt {}}}", m_expression->to_string());
}

PrintStmnt::PrintStmnt(std::shared_ptr<Expr> expression) :
    m_expression(expression) {}
std::string PrintStmnt::to_string() {
    return std::format("{{PrintStmnt {}}}", m_expression->to_string());
}
