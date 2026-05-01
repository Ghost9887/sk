#include <scanner.h>
#include <sk.h>

Scanner::Scanner(const std::string source) :
    m_source(source) {}

std::vector<Token> Scanner::tokenize() {
    while (m_current < static_cast<int>(m_source.length())) {
        m_start = m_current;
        char c { advance() };
        switch (c) {
            case '+': make_token(TokenType::T_PLUS); break;
            case '-': make_token(TokenType::T_MINUS); break;
            case '*': make_token(TokenType::T_STAR); break;
            case '/': make_token(TokenType::T_SLASH); break;
            case '%': make_token(TokenType::T_PERCENT); break;
            case '(': make_token(TokenType::T_LPAREN); break;
            case ')': make_token(TokenType::T_RPAREN); break;
            case '{': make_token(TokenType::T_LBRACE); break;
            case '}': make_token(TokenType::T_RBRACE); break;
            case '.': make_token(TokenType::T_DOT); break;
            case ',': make_token(TokenType::T_COMMA); break;
            case ';': make_token(TokenType::T_SEMICOLON); break;
            case '<': make_token(match_next('=') ? TokenType::T_LESSER_EQUAL : TokenType::T_LESSER); break; 
            case '>': make_token(match_next('=') ? TokenType::T_GREATER_EQUAL : TokenType::T_GREATER); break;
            case '=': make_token(match_next('=') ? TokenType::T_EQUAL_EQUAL : TokenType::T_EQUAL); break;
            case '!': make_token(match_next('=') ? TokenType::T_BANG_EQUAL : TokenType::T_BANG); break;
            case ' ':
            case '\t':
            case '\r':
                break;
            case '\n': m_line++; break;
            case '"': parse_string(); continue;
            default: {
                if (is_digit(c)) {
                    parse_digit(c);
                    continue;
                }else if (is_alpha(c)) {
                    parse_identifier(c);
                    continue;
                }
                SK::error(std::format("Neznamy symbol: {}", c), m_line);
            }break;
        }
    }
    return m_tokens;
}

char Scanner::advance() {
    return m_source.at(m_current++);
}

char Scanner::peek() {
    return m_source.at(m_current);
}

bool Scanner::match_next(const char expected) {
    if (m_current < static_cast<int>(m_source.length()) && m_source.at(m_current) == expected) {
        m_current++;
        return true;
    }
    return false;
}

bool Scanner::is_digit(const char c) {
    return '0' <= c && c <= '9';
}

bool Scanner::is_alpha(const char c) {
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('_' == c);
}

bool Scanner::is_alpha_numeric(const char c) {
    return is_digit(c) || is_alpha(c);
}

void Scanner::parse_digit(const char c) {
    std::string value { c };
    while(is_digit(peek())) value += advance();
    
    if (peek() == '.') {
        value += '.';
        advance();
        while(is_digit(peek())) value += advance();
    }
    make_token(TokenType::T_NUMBER, std::stod(value));
}

void Scanner::parse_identifier(const char c) {
    std::string value { c };
    while(is_alpha_numeric(peek())) value += advance();

    if (keywords_map.find(value) != keywords_map.end()) {
        make_token(keywords_map.at(value));
    }else {
        make_token(TokenType::T_IDENTIFIER);
    }
}

void Scanner::parse_string() {
    std::string str {};
    m_start = m_current;
    while(peek() != '"') str += advance();

    make_token(TokenType::T_STRING, str);
    advance();
}

void Scanner::make_token(const TokenType type) {
    std::string lexeme {m_source.substr(m_start, m_current - m_start)};
    m_tokens.emplace_back(type, m_line, lexeme, std::monostate());
}

void Scanner::make_token(const TokenType type, const Value value) {
    std::string lexeme {m_source.substr(m_start, m_current - m_start)};
    m_tokens.emplace_back(type, m_line, lexeme, value);
}
