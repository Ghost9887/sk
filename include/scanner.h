#ifndef SCANNER_H
#define SCANNER_H

#include <token.h>
#include <vector>

class Scanner {
public:
    Scanner(const std::string source);
    std::vector<Token> tokenize();
    ~Scanner() = default;
private:
    char advance();
    char peek();
    bool match_next(const char expected);
    bool is_digit(const char c);
    bool is_alpha(const char c);
    bool is_alpha_numeric(const char c);
    void parse_digit(const char c);
    void parse_identifier(const char c);
    void parse_string();
    void make_token(const TokenType type);
    void make_token(const TokenType type, const Value value);
private:
    const std::string m_source;
    int m_line { 1 };
    int m_start { 0 };
    int m_current { 0 };
    std::vector<Token> m_tokens {};
};

#endif
