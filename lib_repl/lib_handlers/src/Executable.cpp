#include "Executable.h"
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

std::optional<Executable> Executable::from( const std::string& executable_path ) {

    // determine location
    Executable::Location loc;
    auto first_char = executable_path.front();
    
    if ( (first_char == '/') | (first_char == '\\') ) {

        loc = Executable::Location::ABS;

    } else if ( first_char == '.' ) {

        loc = Executable::Location::REL;

    } else {

        loc = Executable::Location::SYS_PATH;

    }

    switch ( loc ) {

        case Executable::Location::ABS:
            return from_absolute( executable_path );
        
        case Executable::Location::REL:
            return from_relative( executable_path );

        case Executable::Location::SYS_PATH:
            return from_path( executable_path );

    }

    return {};
}

std::optional<Executable> Executable::from_absolute( const std::string& executable_path ) {
    return {};
}

std::optional<Executable> Executable::from_relative( const std::string& executable_path ) {
    return {};
}

std::optional<Executable> Executable::from_path( const std::string& executable_name ) {

    std::string_view path_var = std::getenv("PATH");

    if ( path_var.empty() ) {
        return {};      // return empty if no path variable exists
    }

    // ease of use things for the next section
    using it_dir = std::filesystem::directory_iterator;
    namespace fs = std::filesystem;
    using std::filesystem::perms;
    constexpr auto any_exec_perms = perms::owner_exec | perms::group_exec | perms::others_exec ;
    auto check_entry = [&executable_name](const fs::directory_entry& entry) {
        return 
                ( entry.path().filename() == executable_name ) &&
                ( entry.is_regular_file() ) &&
                ( entry.status().permissions() | any_exec_perms ) != perms::none ?

            std::optional( entry.path() ) : std::nullopt;
    };

    size_t previous_pos = 0;
    size_t current_pos = 0;
    constexpr char delim = ':';

    
    // parse each path variable into a vector of directory iterators
    while ( current_pos < path_var.size() ) {

        current_pos = path_var.find_first_of(delim, previous_pos);

        fs::directory_entry path_var_entry = ( current_pos == std::string::npos ) ?
            fs::directory_entry( path_var.substr(previous_pos) ):
            fs::directory_entry( path_var.substr(previous_pos, current_pos - previous_pos));

        previous_pos = current_pos + 1;

        // short circuit if the entry does not exist
        if ( ! path_var_entry.exists() ) {
            continue;
        }

        // if its not a directory, check if its our target
        if ( ! path_var_entry.is_directory() ) {

            auto possible_exec = check_entry(path_var_entry);

            if ( possible_exec ) {
                return Executable { possible_exec->string(), Executable::Location::SYS_PATH };
            }

            // short circuit if not
            continue;
        }

        // otherwise, iterate through everything in the directory
        std::error_code ec;
        auto dir_entry = fs::begin(it_dir(path_var_entry, ec));

        for (; dir_entry != fs::end(it_dir(path_var_entry)); dir_entry.increment(ec)) {

            // ignore filesystem errors
            if ( ec ) {
                continue;
            }

            auto possible_exec = check_entry(*dir_entry);

            if ( possible_exec ) {
                return Executable{ possible_exec->string(), Executable::Location::SYS_PATH };
            }
        }
    }

    return {};
}
