#include <sk.h>

void SK::run(const std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens { scanner.tokenize() };
    
    std::cout << "-----TOKENS-----" << std::endl;
    for (Token &token : tokens) {
        std::cout << token << std::endl;
    }

    Parser parser(std::move(tokens));
    std::vector<std::shared_ptr<Stmnt>> statements { parser.parse() };

    std::cout << std::endl;
    std::cout << "-----AST-----" << std::endl;
    for (std::shared_ptr<Stmnt> stmnt : statements) {
        std::cout << stmnt->to_string();
        std::cout << std::endl;
    }
}

void SK::error(const std::string message, const int line) {
    std::cerr 
    << std::format("Chyba: {}, Riadok: {}", message, std::to_string(line)) 
    << std::endl;
}
