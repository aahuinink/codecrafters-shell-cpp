#include "error_handling.h"

void ErrorHandler::handle_error(Conditions conditions) {        

    m_err_stack.push(conditions);

    auto handler = m_handle_map.at(conditions.type);

    auto handled = handler(conditions.arg_list);

    if ( ! handled ) {
        panic(conditions.type);
    }
}

bool ErrorHandler::command_not_found(ArgList args) {

    const auto& command = args.at(0);
    
    std::cout << command << ": command not found" << "\n";

    return true;

}

void ErrorHandler::panic(ErrType err) {
    exit(err);
}
