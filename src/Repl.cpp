#include "Repl.h"
#include "DataTypes.h"
#include <iostream>
#include <sstream>

void Repl::run() {

    while (true) {

        // print the prompt
        std::cout << "$ ";

        // get user input
        std::string user_input;
        std::getline(std::cin, user_input);

        Command cmd = parse_input(user_input);

        Error err = m_cmd_handler.run(cmd);

        m_err_handler.handle_error(err);

    }
}

Command Repl::parse_input(std::string& input) {

    bool all_whitespace = Helpers::trim(input);

    if ( all_whitespace ) {
        
        return Command("pass");
        
    } else {

        Command cmd;

        auto cmd_string_len = input.find_first_of(" \n\r\t\v\f");

        if ( cmd_string_len == std::string::npos ) {
            cmd_string_len = input.length();
        }

        cmd.command = input.substr(0, cmd_string_len);

        input.erase(0, cmd_string_len + 1);

        cmd.raw_args = input;

        std::istringstream stream(input);

        std::string arg;

        //create the vector of args
        while ( stream >> arg ) {
            cmd.args.push_back(arg);
        }
        
        return cmd;

    }
}

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
