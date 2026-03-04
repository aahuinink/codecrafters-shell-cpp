#include "Builtins.h"
#include "Executable.h"
#include "common/DataTypes.h"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace Builtins {

Error exit_shell(const Command& cmd) {
    exit(0);
}

Error do_nothing(const Command& cmd) {
    return Error( Error::ErrType::OK );
}

Error echo(const Command& cmd) {

    std::cout << cmd.raw_args << std::endl;

    return Error( Error::ErrType::OK );

}

Error type(const Command& cmd) {

    // if no args are provided
    if ( cmd.args.empty() ) {

        std::cout << "Usage: type <command>\n\tPrints the type of the specified command." << std::endl;
        return Error( Error::ErrType::OK );

    }

    auto builtin_map = get();

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

Error exec(const Command &cmd) {

    //create null-terminated array of char* arguments
    std::vector<char*> argv;
    argv.reserve( cmd.args.size() + 2 );

    argv.push_back( const_cast<char*>( cmd.handler.executable->path.c_str() ));

    for ( auto& arg : cmd.args )
        argv.push_back( const_cast<char*>( arg.c_str() ) );

    argv.push_back(nullptr);

    pid_t child_pid = fork();

    if (child_pid == 0) {
        execv(argv[0], argv.data() );
    }

    int child_status;
    wait( &child_status );

    return Error( Error::ErrType::OK);
}

const CmdHandlerMap& get() noexcept {

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

}
