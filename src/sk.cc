#include <sk.h>

void SK::run(const std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens { scanner.tokenize() };
    
    std::cout << "---TOKENS---" << std::endl;
    for (Token &token : tokens) {
        std::cout << token << std::endl;
    }
}
