#ifndef VM_H
#define VM_H

#include <cstddef>
#include <vector>
#include <stack>
#include "value.h"

enum class OpCode
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

class Vm
{
public:
    Vm(std::vector<std::byte> bytes);
    ~Vm() = default;

    void Interpret();
private:
    void Advance(int amount);
    OpCode ReadCode();
    Value Pop();
    void PushString();
    template<typename T>
    void PushValue();
    void PushNil();
    void Print();
private:
    std::vector<std::byte> mBytes;
    std::size_t mIp {};
    std::stack<Value> mStack {};
};

#endif
