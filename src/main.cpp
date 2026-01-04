#include <ios>
#include <iostream>
#include "Repl.h"

int main() {

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    Repl repl;

    repl.run();

    return 0;
}

