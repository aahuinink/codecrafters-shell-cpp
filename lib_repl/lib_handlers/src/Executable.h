#pragma once
#include <filesystem>
#include <optional>
#include <string>

struct Executable {

    enum Location {
        ABS,
        REL,
        SYS_PATH
    };

    std::filesystem::path path;
    Location loc;
    
    // constructs an Executable object from a string specifying the executable name (if on PATH) or the absolute/relative filepath of the executable.
    static std::optional<Executable> from( const std::string& executable_path );

    // implement function call operator TODO

private:

    static std::optional<Executable> from_absolute( const std::string& executable_path );
    static std::optional<Executable> from_relative( const std::string& executable_path );
    static std::optional<Executable> from_path( const std::string& executable_name );

};
