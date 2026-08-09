#ifndef SK_H
#define SK_H

#include <string>
#include <expected>
#include <cstddef>
#include <vector>

class Sk
{
public:
    Sk(const Sk& instance) = delete;
    Sk& operator=(const Sk&) = delete;
    
    static Sk& GetInstance();
    void Run(int argc, char** argv);
    void Error(const std::string& message);
private:
    Sk() = default;
    ~Sk() = default;
    void PrintUsage();
    std::expected<std::vector<std::byte>, std::string> ReadFile(const char* filePath);
private:
    bool mHadError = false;
};

#endif
