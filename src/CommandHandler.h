#include <functional>
#include <string>
#include <unordered_map>
#include "DataTypes.h"

#pragma once

using namespace DataTypes;

class CommandHandler {
    
    using CmdHandlerFunction = std::function<Error(const std::string&, const StrVec&)>;

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
        { "echo", echo }
    };
    
    // exits the shell, does not actually return anything
    static Error exit_shell(const std::string& raw_args, const StrVec& args);

    // does nothing
    static Error do_nothing(const std::string& raw_args, const StrVec& args);

    // duh
    static Error echo(const std::string& raw_args, const StrVec& args);

};
