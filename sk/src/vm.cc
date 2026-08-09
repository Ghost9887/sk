#include "vm.h"
#include <print>
#include <cstdint>
#include <cstring>

Vm::Vm(std::vector<std::byte> bytes) :
    mBytes(std::move(bytes)) {}

void Vm::Interpret()
{
    while (mIp < mBytes.size())
    {
        OpCode code = ReadCode();
        switch(code)
        {
            case OpCode::STRING: 
                PushString();
                break;
            case OpCode::INT:
                PushValue<int>();
                break;
            case OpCode::DOUBLE: 
                PushValue<double>();
                break;
            case OpCode::BOOLEAN: 
                PushValue<bool>();
                break;
            case OpCode::NIL: 
                PushNil();
                break;
            case OpCode::RETURN: break;
            case OpCode::PRINT: 
                 Print();
                 break;
            case OpCode::ADD: break;
            case OpCode::SUBTRACT: break;
            case OpCode::MULTIPLY: break;
            case OpCode::DIVIDE: break;
            case OpCode::MODULO: break;
            case OpCode::NEW_ENV: break;
            case OpCode::DELETE_ENV: break;
        }
    }
}

void Vm::PushString()
{
    std::uint32_t len {};
    std::memcpy(&len, mBytes.data() + mIp, sizeof(len));
    Advance(sizeof(len));

    std::string str;
    str.resize(len);

    std::memcpy(str.data(), mBytes.data() + mIp, len);
    Advance(len);

    mStack.push(std::move(str));
}

template<typename T>
void Vm::PushValue()
{
    T value {};
    std::memcpy(&value, mBytes.data() + mIp, sizeof(value));
    Advance(sizeof(value));

    mStack.push(value);
}

void Vm::PushNil()
{
    mStack.push(std::monostate());
}

void Vm::Print()
{
    Value value = Pop();
    std::println("{}", ValueToString(value));
}

OpCode Vm::ReadCode()
{
    return static_cast<OpCode>(mBytes[mIp++]);
}

void Vm::Advance(int amount)
{
    mIp += amount;
}

Value Vm::Pop()
{
    Value value = std::move(mStack.top());
    mStack.pop();
    return value;
}
