#include "catch2/catch_test_macros.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include "scanner.h"

TEST_CASE("Tokenize") {
    std::string source;
    std::fstream file("../tests/token_test1.sk");
    std::stringstream buffer;
    buffer << file.rdbuf();
    source = buffer.str();

    Scanner scanner(source);
    std::vector<Token> tokens { scanner.tokenize() };
    std::vector<Token> expected_tokens {};
    expected_tokens.emplace_back(Token(TokenType::T_LPAREN, 1, "(", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_RPAREN, 1, ")", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_LBRACE, 1, "{", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_RBRACE, 1, "}", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_COMMA, 1, ",", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_DOT, 1, ".",  std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_GREATER, 1, ">", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_GREATER_EQUAL, 1, ">=", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_EQUAL_EQUAL, 1, "==", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_LESSER_EQUAL, 1, "<=", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_LESSER, 1, "<", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_BANG, 1, "!", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_BANG_EQUAL, 1, "!=", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_EQUAL, 1, "=", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_IDENTIFIER, 2, "identifier", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_NUMBER, 3, "30", 30.0));
    expected_tokens.emplace_back(Token(TokenType::T_NUMBER, 4, "30.5", 30.5));
    expected_tokens.emplace_back(Token(TokenType::T_STRING, 5, "Hello, World!", "Hello, World!"));
    expected_tokens.emplace_back(Token(TokenType::T_TRIEDA, 6, "trieda", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_AK, 6, "ak", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_FUNK, 6, "funk", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_INAK, 6, "inak", std::monostate()));
    expected_tokens.emplace_back(Token(TokenType::T_VYTLAC, 6, "vytlac", std::monostate()));

    REQUIRE(tokens == expected_tokens);
}
