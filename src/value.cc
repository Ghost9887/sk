#include "value.h"

std::string ValueToString(const Value &value)
{
    return std::visit([](auto &&arg) -> std::string 
    {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            return arg;

        } else if constexpr (std::is_same_v<T, bool>) {
            return arg ? "Pravda" : "Nepravda";

        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(arg);

        } else if constexpr (std::is_same_v<T, std::monostate>) {
            return "Nic";

        } else {
            return "[Neznámy typ]";
        }

    }, value);
}

