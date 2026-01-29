#pragma once
#include "Executable.h"
#include <common/DataTypes.h>
#include <functional>
#include <optional>

using namespace DataTypes;

struct Command {

    struct Handler {
        std::function<Error(const Command&)> builtin;
        std::optional<Executable> executable;
    };

    enum Type {
        BUILTIN,
        EXECUTABLE,
        UNRECOGNIZED
    };

    StrVec args;
    std::string raw_args;
    std::string name;
    Handler handler;
    Type type;

    // factory function that creates a command from a moved-from UserInput object
    static Command from( UserInput&& input );

};
