#include "scanner.hpp"
#include "lox.hpp"

#include <cassert>
#include <map>
#include <iostream>

Scanner::Scanner(std::string source) : source(source) {}

std::list<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(EOFile, "", "", line));
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

void Scanner::scanToken() {
    char c = advance();

    switch(c) {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break; 
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break; 
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) advance();
            } else if (match('*')) {
                // C-style comments
                while ((peek() != '*' && !match('/')) && !isAtEnd()) advance();
                current += 2;
            } else {
            addToken(SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break; 
        case '"': string(); break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                Lox::error(line, "Unexpected character.");
            }
            break;
    };
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();

    const std::string text = source.substr(start, current - start);
    TokenType type;
    try {
        type = keywords.at(text);
    }
    catch(const std::out_of_range& ex) {
        type = IDENTIFIER;
    }
    addToken(type);
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(NUMBER, source.substr(start, current - start));
}

void Scanner::string() {
    while (peek() != '\"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        
        advance();
    }

    if (isAtEnd()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    advance();
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(STRING, value);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;

    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source.at(current + 1);
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}