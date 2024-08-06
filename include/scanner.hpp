#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <list>
#include <map>

#include "token.hpp"

class Scanner {
    std::string source;
    std::list<Token> tokens;

    size_t start   = 0;
    size_t current = 0;
    size_t line    = 1;

    const std::map<std::string, TokenType> keywords = {{"and", AND}, 
                                                       {"class", CLASS}, 
                                                       {"else", ELSE},
                                                       {"false", FALSE},
                                                       {"for", FOR},
                                                       {"fun", FUN},
                                                       {"if",IF},
                                                       {"nil", NIL},
                                                       {"or", OR},
                                                       {"print", PRINT},
                                                       {"return", RETURN},
                                                       {"super", SUPER},
                                                       {"this", THIS},
                                                       {"true", TRUE},
                                                       {"var", VAR},
                                                       {"while", WHILE}
                                                       };

public:
    Scanner(std::string source);

    std::list<Token> scanTokens();

    bool isAtEnd();

    char advance();
    
    void addToken(TokenType type);

    void addToken(TokenType type, std::string literal);

    void scanToken();

    void identifier();

    void number();

    void string();

    bool match(char expected);

    char peek();

    char peekNext();

    bool isAlpha(char c);

    bool isAlphaNumeric(char c);

    bool isDigit(char c);
};

#endif