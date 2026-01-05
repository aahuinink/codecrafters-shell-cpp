#include "CommandHandler.h"
#include "DataTypes.h"
#include <functional>
#include <stdexcept>
#include <iostream>
#include <string>

Error CommandHandler::run(Command& cmd) {
    
    CmdHandlerFunction handler;

    try {

        handler = m_command_map.at(cmd.command);

    } catch (std::out_of_range) {

        Error err( Error::ErrType::INVALID_COMMAND, StrVec{ std::move(cmd.command) } );

        cmd.command = "";

        return err;

    }

    return handler(cmd.raw_args, cmd.args);

}

Error CommandHandler::exit_shell(const std::string& raw_args, const StrVec& args) {
    exit(0);
};

Error CommandHandler::do_nothing(const std::string& raw_args, const StrVec& args) {
    return Error(Error::ErrType::OK);
}

Error CommandHandler::echo(const std::string& raw_args, const StrVec& args) {
    
    std::cout << raw_args << std::endl;

    return Error(Error::ErrType::OK);

}
