#include <functional>
#include <string>
#include <unordered_map>
#include "DataTypes.h"

#pragma once

using namespace DataTypes;

class CommandHandler {

    struct Command {
    
        using HandlerFunction = std::function<Error(const Command&)>;

        enum Type {
            BUILTIN,
            EXECUTABLE,
            UNRECOGNIZED
        };

        StrVec args;
        std::string raw_args;
        std::string name;
        HandlerFunction handler;
        Type type;

    };

    // Maps a string to a handler function
    using CmdHandlerMap = std::unordered_map<
        std::string, 
        Command::HandlerFunction
        >;

    static CmdHandlerMap& get_builtins() {

        // map of command handler functions corresponding to a particular shell command
        static CmdHandlerMap builtin_commands {
            { "pass", do_nothing },
            { "exit", exit_shell },
            { "echo", echo },
            { "type", type },
        };

        return builtin_commands;

    }

    CmdHandlerMap m_builtins_map = get_builtins();


public:

    // runs the command and returns an error structure
    Error evaluate( UserInput&& input );

private:


    // factory function that creates a command from a moved-from UserInput object
    Command command_from( UserInput&& input ) noexcept;
    
    // exits the shell, does not actually return anything
    static Error exit_shell(const Command& cmd);

    // does nothing
    static Error do_nothing(const Command& cmd);

    // duh
    static Error echo(const Command& cmd);

    // prints the type of command (builtin, executable, or unrecognized)
    static Error type(const Command& cmd);

};
