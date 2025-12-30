#include <iostream>
#include <string>
#include "error_handling.h"


int main() {

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    ErrorHandler err_handler;

    // print the prompt
    std::cout << "$ ";

    // get user input
    std::string user_input;
    std::getline(std::cin, user_input);

    err_handler.handle_error(ErrorHandler::Conditions(ErrType::INVALID_COMMAND, user_input));

}
