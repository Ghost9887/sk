#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>
#include "scanner.h"
#include "parser.h"
#include "token.h"
#include "stmnt.h"
#include "expr.h"

TEST_CASE("token_test")
{
    std::ifstream file("../tests/token_test.sk");
    REQUIRE(file.is_open());

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    Scanner scanner(content);
    std::vector<Token> given = scanner.Tokenize();

    std::vector<Token> expected = {
        Token(TokenType::LPAREN, 1, 1, "(", std::monostate{}),
        Token(TokenType::RPAREN, 1, 2, ")", std::monostate{}),
        Token(TokenType::STRING, 2, 1, "Hello, World", std::string("Hello, World")),
        Token(TokenType::INT, 3, 1, "30", 30),
        Token(TokenType::DOUBLE, 4, 1, "30.2", 30.2),
        Token(TokenType::BOOLEAN, 5, 1, "pravda", true),
        Token(TokenType::EQUAL_EQUAL, 6, 1, "==", std::monostate{}),
        Token(TokenType::IF, 7, 1, "ak", std::monostate{}),
        Token(TokenType::ELSE, 8, 1, "inak", std::monostate{})
    };

    REQUIRE(given.size() == expected.size());

    for (std::size_t i = 0; i < given.size(); ++i)
        CHECK(given[i] == expected[i]);
}

TEST_CASE("parser_test")
{
    std::ifstream file("../tests/parse_test.sk");
    REQUIRE(file.is_open());

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    Scanner scanner(content);
    std::vector<Token> tokens = scanner.Tokenize();
    Parser parser(std::move(tokens));
    std::vector<std::unique_ptr<Stmnt>> given = parser.Parse();
    std::string expected = "PrintStmnt[BinaryExpr[ValueExpr[5] Plus ValueExpr[5]]]";

    REQUIRE(given[0]->ToString() == expected);
}

