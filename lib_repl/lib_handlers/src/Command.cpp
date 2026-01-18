#include "Command.h"
#include "Builtins.h"

Command Command::from( UserInput&& input ) noexcept {

    Command cmd;

    cmd.args = std::move( input.args );
    cmd.raw_args = std::move( input.raw_args );
    cmd.name = std::move( input.command );

    CmdHandlerMap builtins = Builtins::get();

    auto it = builtins.find( cmd.name );

    if ( it != builtins.end() ) {

        cmd.handler = it->second;
        cmd.type = Command::Type::BUILTIN;

    } else {
    
        cmd.handler = Builtins::exit_shell;               // exit if we try to execute an unrecognized command
        cmd.type = Command::Type::UNRECOGNIZED;

    }

    return cmd;

}
