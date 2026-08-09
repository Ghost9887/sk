#include "sk.h"

Sk::Sk() = default;
Sk::~Sk() = default;

void Sk::Run([[maybe_unused]]int argc, [[maybe_unused]]char **argv)
{
}

Sk& Sk::GetInstance()
{
    static Sk instance; 
    return instance;
}
