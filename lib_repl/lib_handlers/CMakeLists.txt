add_library(handlers STATIC)

target_sources(handlers
    PRIVATE
        src/CommandHandler.cpp
        src/ErrorHandler.cpp
        src/Command.cpp
        src/Builtins.cpp
    PRIVATE FILE_SET HEADERS
    BASE_DIRS src/
    FILES src/Command.h src/Builtins.h
)

target_include_directories(handlers
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(handlers PRIVATE common)
