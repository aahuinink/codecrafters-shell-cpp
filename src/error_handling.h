#include <array>
#include <map>
#include <stack>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

// Error types
enum ErrType {
    INVALID_COMMAND,
};


// error handler object
class ErrorHandler {

    using ArgList = std::vector<std::string>;

public:
    
    struct Conditions {
        ErrType type;
        ArgList arg_list;

        Conditions(ErrType err_type, std::string params...) :
            type(err_type),
            arg_list({params})
        {};
    };

private:

    // stack of errors
    std::stack<Conditions> m_err_stack;

    // map of function handlers
    std::unordered_map<ErrType, std::function<bool(ArgList)>> m_handle_map {
        { ErrType::INVALID_COMMAND, command_not_found },
    };

public:

    ErrorHandler();
    ~ErrorHandler();
   
    // handles a custom error, panics as necessary
    void handle_error(const Conditions conditions);
    
private:

    static bool command_not_found(ArgList args);

    void panic();
};
