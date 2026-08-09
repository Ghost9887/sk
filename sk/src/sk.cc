#include "sk.h"
#include "vm.h"
#include <print>
#include <fstream>

void Sk::Run(int argc, char** argv)
{
    if (argc != 2)
    {
        PrintUsage();
        return;
    }

    auto content = ReadFile(argv[1]);
    if (!content)
        Error(content.error());

    if (mHadError) return;

    Vm vm(std::move(content.value()));
    vm.Interpret();
}

std::expected<std::vector<std::byte>, std::string> Sk::ReadFile(const char* filePath)
{
    std::ifstream input(filePath, std::ios::binary);
    if (!input)
        return std::unexpected(std::format("Nenašiel sa súbor: '{}'", filePath));

    input.seekg(0, std::ios::end);
    std::size_t size = input.tellg();
    input.seekg(0, std::ios::beg);

    std::vector<std::byte> bytes(size);
    input.read(reinterpret_cast<char*>(bytes.data()), size);

    return bytes;
}

Sk& Sk::GetInstance()
{
    static Sk instance; 
    return instance;
}

void Sk::Error(const std::string& message)
{
    std::println("{}", message);
    mHadError = true;
}

void Sk::PrintUsage()
{
    std::println("Pouzitie: sk <nazov suboru>");
}
