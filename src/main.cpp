#include <ios>
#include <iostream>
#include <string>
#include "Repl.h"

bool trim(std::string &str);

int main() {

    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    ErrorHandler err_handler;

    while (true) {
        // print the prompt
        std::cout << "$ ";

        // get user input
        std::string user_input;
        std::getline(std::cin, user_input);

        bool not_all_whitespace = trim(user_input);

        if ( not_all_whitespace ) {

            err_handler.handle_error(ErrorHandler::Conditions(ErrType::INVALID_COMMAND, user_input));

        } else {

            continue;

        }
    }
}

// @brief       Removes all leading and trailing whitespace
// @param       Ref to string to modify
// @returns     True if there is still string leftover, false if str was all whitespace
bool trim(std::string &str) {
    auto start_index = str.find_first_not_of(" \t\r\n\f\v");
    auto end_index = str.find_last_not_of(" \t\r\f\v\n");

    // if all whitespace
    if ( start_index == std::string::npos ) {

        return false;

    } else {
        
        // trim end, then beginning
        if ( end_index != str.size() - 1 ) {
            str.erase(end_index + 1);
        }

        if ( start_index != 0 ) {
            str.erase(0, start_index);
        }

        return true;

    }
}
