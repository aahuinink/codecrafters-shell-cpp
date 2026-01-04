#include "CommandHandler.h"
#include "DataTypes.h"
#include <functional>
#include <stdexcept>

Error CommandHandler::run(Command& cmd) {
    
    CmdHandlerFunction handler;

    try {

        handler = m_command_map.at(cmd.command);

    } catch (std::out_of_range) {

        Error err( Error::ErrType::INVALID_COMMAND, StrVec{ std::move(cmd.command) } );

        return err;

    }

    return handler(cmd.args);

}

Error CommandHandler::exit_shell(StrVec args) {
    exit(0);
};

Error CommandHandler::do_nothing(StrVec args) {
    return Error(Error::ErrType::OK);
}
