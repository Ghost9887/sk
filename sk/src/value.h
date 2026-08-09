#ifndef VALUE_H
#define VALUE_H

#include <variant>
#include <string>

using Value = std::variant<std::monostate, int, double, std::string, bool>;

std::string ValueToString(const Value& value);

#endif
