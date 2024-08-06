#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "tokentype.hpp"

class Token {
    TokenType type;
    std::string lexeme;
    std::string literal;
    int line;

public:
    Token(TokenType type, std::string lexeme, std::string literal, int line);
    
    std::string toString();
};

std::string typeToString (TokenType type);

#endif