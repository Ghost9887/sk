#ifndef SK_H
#define SK_H

#include <string>
#include <expected>

class Token;

class Sk
{
public:
    Sk(const Sk& instance) = delete;
    Sk& operator=(const Sk&) = delete;

    static Sk& GetInstance();
    void Error(const std::string& message, const Token* token);
    void Run(int argc, char **argv);
private:
    Sk();
    ~Sk();

    void PrintHelp();
    std::expected<std::string, std::string> ReadFile(const char *filePath);
    std::string GetLine(std::size_t lineNumber);
    std::string GetLocation(std::size_t column);
private:
    std::string mContent;
    bool mHadError;
};

#endif
