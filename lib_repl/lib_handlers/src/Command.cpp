#include "Command.h"
#include "Builtins.h"
#include "Executable.h"

Command Command::from( UserInput&& input ) {

    Command cmd;

    cmd.args = std::move( input.args );
    cmd.raw_args = std::move( input.raw_args );
    cmd.name = std::move( input.command );

    CmdHandlerMap builtins = Builtins::get();

    auto it = builtins.find( cmd.name );

    if ( it != builtins.end() ) {
    
        cmd.handler = Handler{ it->second, {} };
        cmd.type = Command::Type::BUILTIN;

    } else if ( auto executable = Executable::from( cmd.name ) ) {
        
        cmd.handler = Handler{ Builtins::exec, executable };
        cmd.type = Command::Type::EXECUTABLE;

    } else {
    
        cmd.handler = Handler{ Builtins::exit_shell, {} };               // exit if we try to execute an unrecognized command
        cmd.type = Command::Type::UNRECOGNIZED;

    }

    return cmd;

}
