#include "commands.h"

ErrType CommandHandler::run(Config config) {
    
}

ErrType CommandHandler::exit_shell(ArgList args) {
    
    exit(0);

    return ErrType::NULL_ERR;

}
