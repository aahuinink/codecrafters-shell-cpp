#include "CommandHandler.h"
#include "DataTypes.h"
#include "ErrorHandler.h"

#pragma once

using namespace DataTypes;

// Implements the REPL
class Repl {

    CommandHandler m_cmd_handler;

    ErrorHandler m_err_handler;

public:

    // runs the REPL
    void run();

private:

    // @brief           Creates a command from user input
    // @param   input   The user input to parse
    // @returns         The command object to run
    Command parse_input(std::string& input);

    struct Helpers {

        // @brief       Determines if a string is all whitespace, then trims all trailing and leading whitespace
        // @param str   The string to modify
        // @returns     True if the string is all whitespace, False if it isn't
        static bool trim(std::string& str);

    };

};
