#include <functional>
#include <string>
#include <unordered_map>
#include "error_handling.h"

class CommandHandler {

    using ArgList = std::vector<std::string>;

public:

    struct Config {

        // public members
        std::string command;
        ArgList args;

        // constructor
        Config(std::string cmd, std::string arg_list...) :
            command(cmd),
            args({arg_list})
            {};

    };
    
    // runs the command with the args provided in the config
    ErrType run(Config config);

private:

    std::unordered_map<std::string, std::function<ErrType(ArgList)>> m_command_map {
        { "exit", exit_shell },
    };

    ErrorHandler m_error_handler;

    static ErrType exit_shell(ArgList args);

};
