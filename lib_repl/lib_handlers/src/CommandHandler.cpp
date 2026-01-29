#include <handlers/CommandHandler.h>
#include "Command.h"
#include <string>

using namespace DataTypes;

Error CommandHandler::evaluate( UserInput&& input ) {
    
    Command cmd = Command::from( std::move(input) );

    if ( cmd.type == Command::Type::UNRECOGNIZED ) {
        return Error(Error::ErrType::INVALID_COMMAND, cmd.name );
    }

    return cmd.handler.builtin(cmd);

};

