#include "Repl.h"
#include "DataTypes.h"
#include <iostream>
#include <sstream>

void Repl::run() {

    while (true) {

        // print the prompt
        std::cout << "$ ";

        // get user input
        std::string raw_input;
        std::getline(std::cin, raw_input);

        UserInput parsed_input = parse_input( std::move(raw_input) );

        Error err = m_cmd_handler.evaluate( std::move(parsed_input) );

        m_err_handler.handle_error(err);

    }
}

// @brief       Parses some raw input into a UserInput object
// @return      The created UserInput object
UserInput Repl::parse_input(std::string&& raw_input) {

    bool all_whitespace = Helpers::trim(raw_input);

    if ( all_whitespace ) {
        
        return UserInput("pass");
        
    } else {

        UserInput parsed_input;

        auto cmd_string_len = raw_input.find_first_of(" \n\r\t\v\f");   // find the end of the first expression in the input

        if ( cmd_string_len == std::string::npos ) {
            cmd_string_len = raw_input.length();
        }

        parsed_input.command = raw_input.substr(0, cmd_string_len);

        raw_input.erase(0, cmd_string_len + 1);

        parsed_input.raw_args = raw_input;

        std::istringstream stream(raw_input);

        std::string arg;

        //create the vector of args
        while ( stream >> arg ) {
            parsed_input.args.push_back(arg);
        }
        
        return parsed_input;

    }
}

// @brief       Removes all leading whitespace from a string
// @return      Returns true if the string is all whitespace, false if not
bool Repl::Helpers::trim(std::string &str) {

    auto start_index = str.find_first_not_of(" \t\r\n\f\v");

    // if all whitespace
    if ( start_index == std::string::npos ) {

        return true;

    } else {
        
        str.erase(0, start_index);
        return false;

    }
}
