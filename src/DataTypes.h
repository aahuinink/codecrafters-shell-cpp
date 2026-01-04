#include <string>
#include <vector>

#pragma once

namespace DataTypes {
    
    using StrVec = std::vector<std::string>;

    // Represents a command, created by the input parser
    struct Command {

        std::string command;    // the command to run
        StrVec args;            // list of associated args
        
        Command() = default;

        Command(std::string cmd, StrVec&& args) :
            command(cmd),
            args(args)
        {};

        template <typename... Args>
        Command(std::string&& cmd, Args&&... args) :
            command(cmd),
            args( { static_cast<std::string>(args)... } )
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

        Error(ErrType err_type, StrVec&& additional_info) :
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
