#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <string>

namespace Lox {
    static bool hadError = false;

    void runFile(std::string path) {
        std::string line;
        std::string code;

        std::ifstream in(path);
        
        if (in.is_open()) {
            while (std::getline(in, line)) {
                code += line;
            }
        }

        in.close();

        run(code);

        if (hadError) exit(65);
    }

    void runPrompt() {
        while (true) {
            std::cout << "> ";

            std::string line;
            std::getline(std::cin, line);

            if (line.length() == 0) break;
            run(line);
            hadError = false;
        }
    }

    void run(std::string source) {
        Scanner* scanner = new Scanner(source);
        std::list<Token> tokens = scanner->scanTokens();

        // For now, just print the tokens.
        for (Token& token : tokens) {
            std::cout << token.toString() << std::endl;
        }

        delete scanner;
    }


    void error(int line, std::string message) {
        report(line, "", message);
    }
    
    void report(int line, std::string where, std::string message) {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
        hadError = true;
    }
};