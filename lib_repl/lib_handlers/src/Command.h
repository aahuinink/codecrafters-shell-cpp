#pragma once
#include <common/DataTypes.h>
#include <functional>

using namespace DataTypes;

struct Command {

    using HandlerFunction = std::function<Error(const Command&)>;

    enum Type {
        BUILTIN,
        EXECUTABLE,
        UNRECOGNIZED
    };

    StrVec args;
    std::string raw_args;
    std::string name;
    HandlerFunction handler;
    Type type;

    // factory function that creates a command from a moved-from UserInput object
    static Command from( UserInput&& input ) noexcept;

};

