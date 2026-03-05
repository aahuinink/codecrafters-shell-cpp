#include "Builtins.h"
#include "Executable.h"
#include "common/DataTypes.h"
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <linux/close_range.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#define EXECUTION_TIMEOUT 5000          // Number of ms to wait for a child process to execute before killing it

namespace Builtins {

Error exit_shell(const Command& cmd) {
    exit(0);
}

Error do_nothing(const Command& cmd) {
    return Error( Error::ErrType::OK );
}

Error echo(const Command& cmd) {

    std::cout << cmd.raw_args << std::endl;

    return Error( Error::ErrType::OK );

}

Error type(const Command& cmd) {

    // if no args are provided
    if ( cmd.args.empty() ) {

        std::cout << "Usage: type <command>\n\tPrints the type of the specified command." << std::endl;
        return Error( Error::ErrType::OK );

    }

    auto builtin_map = get();

    auto command_to_type = cmd.args[0];

    auto it = builtin_map.find( command_to_type );

    if ( it != builtin_map.end() ) {

        std::cout << command_to_type << " is a shell builtin" << std::endl;

    } else if ( auto executable = Executable::from( command_to_type )) {

        std::cout << command_to_type << " is " << executable->path << std::endl;

    } else {

        std::cout << command_to_type << ": not found" << std::endl;

    }

    return Error( Error::ErrType::OK );
}

// TODO refactor this into a running process handler for child processes
Error exec(const Command &cmd) {

    // use self-pipe trick to monitor child process:  https://stackoverflow.com/questions/1584956/how-to-handle-execvp-errors-after-fork
    int pipefds[2];

    // create pipe
    if ( pipe(pipefds) ) {
        std::cerr << "Failed to create pipe for child process: " << std::strerror(errno) << std::endl;
        return Error ( Error::ErrType::OS );
    }

    // set close-after-exec flag on write end of pipe (in addition to whatever is currently set)
    if ( fcntl( pipefds[1], F_SETFD, fcntl( pipefds[1], F_GETFD ) | FD_CLOEXEC ) ) {
        std::cerr << "Failed to set file permisions on pipe: " << std::strerror(errno) << std::endl;
        return Error ( Error::ErrType::OS );
    }

    pid_t child_pid = fork();
    int count, status;

    switch ( child_pid ) {

        case -1: {
            std::cerr << "Failed to fork the child process: " << std::strerror(errno) << std::endl;
            return Error( Error::ErrType::FORK_FAILED );
        }

        case 0: {

            close( pipefds[0] );    // close child read end
            
            //create null-terminated array of char* arguments for exec call
            std::vector<char*> argv;
            argv.reserve( cmd.args.size() + 2 );

            argv.push_back( const_cast<char*>( cmd.name.c_str() ));

            for ( auto& arg : cmd.args )
                argv.push_back( const_cast<char*>( arg.c_str() ) );

            argv.push_back(nullptr);

            execv( cmd.handler.executable.path.c_str(), argv.data() ) ;

            // child write end closes here if exec succeeds, otherwise it still exists and we can write errors to it
            write( pipefds[1], &errno, sizeof( errno ) );
            _exit(0);
        }

        default:
            close( pipefds[1] );

            struct pollfd pollfd;

            pollfd.fd = pipefds[0];
            pollfd.events = POLLIN | POLLHUP;

            // non-blocking read on the pipe. If the process takes too long to exec, kill it.
            count = poll( &pollfd, 1, EXECUTION_TIMEOUT );

            switch ( count ) {
                case -1:
                    std::cerr << "Unable to poll child process: " << std::strerror(errno) << std::endl;
                    return Error ( Error::ErrType::OS );
                case 0:
                    std::cerr << "Child process did not start within timelimit. Killing it..." << std::endl;
                    kill( child_pid , SIGKILL );
                    break;
                default:
                    // if an error in the exec call occurs, read it in
                    if ( pollfd.revents & POLLIN ) {
                        read( pipefds[0], &status, sizeof(int) );
                        std::cerr << "Child process exectution failed! " << std::strerror( status ) << std::endl;
                        return Error ( Error::ErrType::EXEC_FAILED );
                    }

                    // otherwise, wait for the child to finish
                    waitpid( child_pid, &status, 0);

                    // if the call to wait fails because of something other than the child exiting before the call
                    // (we know the child exists before this point bc we've checked the return of fork())
                    if ( errno && ( errno != ECHILD ) ) {
                        std::cerr << "Failed to wait for child process: " << std::strerror(errno) << std::endl;
                    }
                    // do nothing with status for now, but eventually we will?
            }
            
    }
    return Error( Error::ErrType::OK);
}

Error pwd(const Command& cmd) {
    std::cout << std::filesystem::current_path().c_str() << std::endl; 
    return Error ( Error::ErrType::OK );
}

const CmdHandlerMap& get() noexcept {

        // map of command handler functions corresponding to a particular shell command
        static CmdHandlerMap builtin_commands {
            { "pass", do_nothing },
            { "exit", exit_shell },
            { "echo", echo },
            { "type", type },
            { "exec", exec },
            { "pwd",  pwd  }
        };

        return builtin_commands;

}

}
