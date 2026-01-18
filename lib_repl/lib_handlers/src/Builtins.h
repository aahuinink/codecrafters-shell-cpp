#pragma once
#include "Command.h"

// Maps a string to a handler function
using CmdHandlerMap = std::unordered_map<
    std::string, 
    Command::HandlerFunction
>;

namespace Builtins {
    
    // exits the shell, does not actually return anything
    Error exit_shell(const Command& cmd);

    // does nothing
    Error do_nothing(const Command& cmd);

    // duh
    Error echo(const Command& cmd);

    // prints the type of command (builtin, executable, or unrecognized)
    Error type(const Command& cmd);
    
    const CmdHandlerMap& get() noexcept;

}
