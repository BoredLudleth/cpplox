#include "lox.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "Usage: jlox [script]" << std::endl;
        exit(64); 
    } else if (argc == 2) {
        Lox::runFile(argv[1]);
    } else {
        Lox::runPrompt();
    }
}