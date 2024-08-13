#ifndef LOX_HPP
#define LOX_HPP

#include <string>

namespace Lox {
    extern bool hadError;

    void runFile(std::string path);

    void runPrompt();

    void run(std::string source);

    void error(int line, std::string message);

    void report(int line, std::string where, std::string message);
};

#endif