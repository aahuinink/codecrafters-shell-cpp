#include "Repl.h"
#include "DataTypes.h"
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

        std::istringstream stream(input);

        std::string arg;

        stream >> cmd.command;

        while ( stream >> arg ) {
            cmd.args.push_back(arg);
        }
        
        return cmd;

    }
}

bool Repl::Helpers::trim(std::string &str) {

    auto start_index = str.find_first_not_of(" \t\r\n\f\v");
    auto end_index = str.find_last_not_of(" \t\r\f\v\n");

    // if all whitespace
    if ( start_index == std::string::npos ) {

        return true;

    } else {
        
        // trim end, then beginning
        if ( end_index != str.size() - 1 ) {
            str.erase(end_index + 1);
        }

        if ( start_index != 0 ) {
            str.erase(0, start_index);
        }

        return false;

    }
}
