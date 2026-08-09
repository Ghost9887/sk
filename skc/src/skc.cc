#include "skc.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "compiler.h"
#include <fstream>
#include <sstream>
#include <print>
#include <memory>

#define DEBUG_MODE

Skc::Skc() :
    mHadError(false) {}

Skc::~Skc() = default;

void Skc::Run(int argc, char **argv)
{
    if (argc != 2)
    {
        PrintHelp();
        return;
    }

    auto content = ReadFile(argv[1]);
    if (!content)
        Error(content.error(), nullptr);

    if (mHadError) return;   
    mContent = std::move(content.value());   
    Scanner scanner(mContent);
    std::vector<Token> tokens = scanner.Tokenize();
#ifdef DEBUG_MODE
    std::println("-----TOKENS-----");
    for (auto& token : tokens)
    {
        std::println("{}", token.ToString());       
    }
#endif
    Parser parser(std::move(tokens));
    std::vector<std::unique_ptr<Stmnt>> statements = parser.Parse();
    if (mHadError) return;
#ifdef DEBUG_MODE
    std::println("\n-----AST-----");
    for (std::size_t i {}; i < statements.size(); ++i)
    {
        std::println("{}", statements[i]->ToString());
    }
#endif

    Compiler compiler(statements);
    compiler.Compile();
}

Skc& Skc::GetInstance()
{
    static Skc instance;
    return instance;
}

void Skc::PrintHelp()
{
    std::println("Použitie: sk <názov súboru>");
}

std::expected<std::string, std::string> Skc::ReadFile(const char *filePath)
{
    std::ifstream file(filePath);

    if(!file.is_open())
        return std::unexpected(std::format("Súbor '{}' sa nenašiel", filePath));

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void Skc::Error(const std::string& message, const Token* token)
{
    if (token) {
        std::println("\nCHYBA: {} Riadok: {} | Poloha: {}\n{}\n{}", 
                message, 
                token->GetLine(),
                token->GetColumn(),
                GetLine(token->GetLine()), 
                GetLocation(token->GetColumn()));
    }else std::println("\nCHYBA: {}\n", message);
    mHadError = true;
};


std::string Skc::GetLine(std::size_t lineNumber)
{
    std::size_t currentLine = 1;
    std::string line;

    for (char c : mContent)
    {
        if (c == '\n')
        {
            if (currentLine == lineNumber)
                return line;

            line.clear();
            currentLine++;
        }
        else
        {
            line += c;
        }
    }
    if (currentLine == lineNumber)
        return line;

    return "";
}

std::string Skc::GetLocation(std::size_t column)
{
    std::string location {};
    for (std::size_t i {}; i < column; ++i)
    {
        location += '~';
    }
    location += '^';
    return location;
}

