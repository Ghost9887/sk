#include <debugger.h>

std::string Debugger::value_to_string(const Value value) {
    return std::visit([](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return arg;
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(arg);
        } else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "pravda" : "nepravda";
        } else {
            return "nic";
        }
    }, value);
}
