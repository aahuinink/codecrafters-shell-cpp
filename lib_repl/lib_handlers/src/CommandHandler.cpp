#include <handlers/CommandHandler.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace DataTypes;

CommandHandler::Command CommandHandler::command_from( UserInput&& input ) noexcept {
    
    CommandHandler::Command cmd;

    cmd.args = std::move( input.args );
    cmd.raw_args = std::move( input.raw_args );
    cmd.name = std::move( input.command );

    auto it = m_builtins_map.find( cmd.name );

    if ( it != m_builtins_map.end() ) {

        cmd.handler = it->second;
        cmd.type = Command::Type::BUILTIN;

    } else {
    
        cmd.handler = exit_shell;               // exit if we try to execute an unrecognized command
        cmd.type = Command::Type::UNRECOGNIZED;

    }

    return cmd;
}

Error CommandHandler::evaluate( UserInput&& input ) {
    
    Command cmd = command_from( std::move(input) );

    if ( cmd.type == Command::Type::UNRECOGNIZED ) {
        return Error(Error::ErrType::INVALID_COMMAND, cmd.name );
    }

    return cmd.handler(cmd);

};

Error CommandHandler::exit_shell(const Command& cmd) {
    exit(0);
}

Error CommandHandler::do_nothing(const Command& cmd) {
    return Error( Error::ErrType::OK );
}

Error CommandHandler::echo(const Command& cmd) {

    std::cout << cmd.raw_args << std::endl;

    return Error( Error::ErrType::OK );

}

Error CommandHandler::type(const Command& cmd) {

    if ( cmd.args.empty() ) {

        std::cerr << "Usage: type <command>\n\tPrints the type of the specified command." << std::endl;

        return Error( Error::ErrType::OK );

    }

    auto builtin_map = get_builtins();

    auto command_to_type = cmd.args[0];

    auto it = builtin_map.find( command_to_type );

    if ( it != builtin_map.end() ) {

        std::cout << command_to_type << " is a shell builtin" << std::endl;

    } else {

        std::cout << command_to_type << ": not found" << std::endl;

    }

    return Error( Error::ErrType::OK );
}
