#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include "error_handling.h"


int main() {

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    ErrorHandler err_handler;

    while (true) {
        // print the prompt
        std::cout << "$ ";

        // get user input
        std::string user_input, args;
        std::cin >> user_input;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        err_handler.handle_error(ErrorHandler::Conditions(ErrType::INVALID_COMMAND, user_input));
    }
}
