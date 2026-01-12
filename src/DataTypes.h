#include <string>
#include <vector>

#pragma once

namespace DataTypes {
    
    using StrVec = std::vector<std::string>;

    // Represents a command, created by the input parser
    struct UserInput {

        StrVec args;            // list of associated args
        std::string command;    // the command to run
        std::string raw_args;   // the raw input
        
        UserInput() = default;

        UserInput(std::string&& cmd, std::string&& raw_args, StrVec&& args) :
            command(std::move(cmd)),
            raw_args(std::move(raw_args)),
            args(std::move(args))
        {};

        UserInput(std::string&& cmd) :
            command(std::move(cmd)),
            raw_args(""),
            args( { } )
            {};

    };

    struct Error {

        enum ErrType {
            OK,
            INVALID_COMMAND,
        };

        ErrType type;
        StrVec info;

        Error() = default;

        Error(ErrType err_type, StrVec additional_info) :
            type(err_type),
            info(additional_info)
        {};
        
        template <typename... AdditionalInfoPack>
        Error(ErrType err_type, AdditionalInfoPack... additional_info) :
            type( err_type ),
            info( { static_cast<std::string>(additional_info)... } )
        {};
    };

}
