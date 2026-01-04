#include "ErrorHandler.h"

void ErrorHandler::handle_error(const Error err) {        

    auto handler = m_handler_map.at(err.type);

    auto handled = handler(err.info);

    if ( ! handled ) {
        panic(err.type);
    }
}

bool ErrorHandler::command_not_found( StrVec info) {

    const auto& command = info.at(0);
    
    std::cout << command << ": command not found" << std::endl;

    return true;

}

void ErrorHandler::panic(Error::ErrType err_type) {
    exit(err_type);
}
