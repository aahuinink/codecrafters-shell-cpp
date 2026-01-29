#pragma once
#include "Command.h"
#include <functional>

// Maps a string to a handler function
using CmdHandlerMap = std::unordered_map<
    std::string, 
    std::function<Error (const Command&)>
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

    // creates a process
    Error exec(const Command& cmd);
    
    // returns a map of builtin functions
    const CmdHandlerMap& get() noexcept;

}
