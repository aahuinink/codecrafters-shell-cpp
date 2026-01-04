#include <functional>
#include <string>
#include <unordered_map>
#include "DataTypes.h"

#pragma once

using namespace DataTypes;

class CommandHandler {
    
    using CmdHandlerFunction = std::function<Error(StrVec)>;

    // Maps a string to a handler function
    using CmdHandlerMap = std::unordered_map<
        std::string, 
        CmdHandlerFunction
        >;

public:

    // runs the command and returns an error structure
    Error run(Command& cmd);

private:
    
    // map of command handler functions corresponding to a particular shell command
    CmdHandlerMap m_command_map {
        { "pass", do_nothing },
        { "exit", exit_shell },
    };
    
    // exits the shell, does not actually return anything
    static Error exit_shell(StrVec args);

    // does nothing
    static Error do_nothing(StrVec args);

};
