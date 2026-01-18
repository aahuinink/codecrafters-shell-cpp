add_subdirectory(lib_handlers)
add_subdirectory(lib_common)

add_library(repl STATIC)

target_sources(repl
    PRIVATE
        src/Repl.cpp
)

target_include_directories(repl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(repl PRIVATE common handlers)
