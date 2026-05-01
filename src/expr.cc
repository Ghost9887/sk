#include <expr.h>

ValueExpr::ValueExpr(Value value) :
    m_value(value) {}
std::string ValueExpr::to_string() {
    return std::format("{{ValueExpr {}}}", Debugger::value_to_string(m_value));
}

BinaryExpr::BinaryExpr(std::shared_ptr<ValueExpr> left, Token op, std::shared_ptr<ValueExpr> right) :
    m_left(left), m_op(op), m_right(right) {}
std::string BinaryExpr::to_string() {
    return std::format("{{BinaryExpr {} ; {} ; {}}}", m_left->to_string(), m_op.get_lexeme(), m_right->to_string());
}
