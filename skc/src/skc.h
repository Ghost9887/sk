#ifndef SKC_H
#define SKC_H

#include <string>
#include <expected>

class Token;

class Skc
{
public:
    Skc(const Skc& instance) = delete;
    Skc& operator=(const Skc&) = delete;

    static Skc& GetInstance();
    void Error(const std::string& message, const Token* token);
    void Run(int argc, char **argv);
private:
    Skc();
    ~Skc();

    void PrintHelp();
    std::expected<std::string, std::string> ReadFile(const char *filePath);
    std::string GetLine(std::size_t lineNumber);
    std::string GetLocation(std::size_t column);
private:
    std::string mContent;
    bool mHadError;
};

#endif
