#include <common/DataTypes.h>

#pragma once

using namespace DataTypes;

class CommandHandler {

public:

    // runs the command and returns an error structure
    Error evaluate( UserInput&& input );

};
