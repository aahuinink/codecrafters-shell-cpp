#include "Builtins.h"
#include "Executable.h"
#include "common/DataTypes.h"
#include <iostream>

Error Builtins::exit_shell(const Command& cmd) {
    exit(0);
}

Error Builtins::do_nothing(const Command& cmd) {
    return Error( Error::ErrType::OK );
}

Error Builtins::echo(const Command& cmd) {

    std::cout << cmd.raw_args << std::endl;

    return Error( Error::ErrType::OK );

}

Error Builtins::type(const Command& cmd) {

    // if no args are provided
    if ( cmd.args.empty() ) {

        std::cout << "Usage: type <command>\n\tPrints the type of the specified command." << std::endl;
        return Error( Error::ErrType::OK );

    }

    auto builtin_map = Builtins::get();

    auto command_to_type = cmd.args[0];

    auto it = builtin_map.find( command_to_type );

    if ( it != builtin_map.end() ) {

        std::cout << command_to_type << " is a shell builtin" << std::endl;

    } else if ( auto executable = Executable::from( command_to_type )) {

        std::cout << command_to_type << " is " << executable->path << std::endl;

    } else {

        std::cout << command_to_type << ": not found" << std::endl;

    }

    return Error( Error::ErrType::OK );
}

Error Builtins::exec(const Command &cmd) {
    return Error( Error::ErrType::OK );
}

const CmdHandlerMap& Builtins::get() noexcept {

        // map of command handler functions corresponding to a particular shell command
        static CmdHandlerMap builtin_commands {
            { "pass", do_nothing },
            { "exit", exit_shell },
            { "echo", echo },
            { "type", type },
            { "exec", exec },
        };

        return builtin_commands;

}
