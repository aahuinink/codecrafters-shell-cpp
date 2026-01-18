#include <functional>
#include <unordered_map>
#include <common/DataTypes.h>

#pragma once

using namespace DataTypes;

// error handler object
class ErrorHandler {
    
    using ErrHandlerFunc = std::function< bool ( const StrVec ) >;

    using ErrHandlerMap = std::unordered_map<
        Error::ErrType, 
        ErrHandlerFunc
        >;

    // map of function handlers
    ErrHandlerMap m_handler_map {
        { Error::ErrType::OK, ok },
        { Error::ErrType::INVALID_COMMAND, command_not_found },
    };

public:

    // handles an error, panics as necessary
    void handle_error(const Error err);
    
private:

    static bool command_not_found(const StrVec err_info);

    static bool ok(const StrVec err_info) { return true; };

    void panic(Error::ErrType err_type);

};
