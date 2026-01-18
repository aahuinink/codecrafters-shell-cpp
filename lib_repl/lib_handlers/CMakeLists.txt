add_library(handlers STATIC)

target_sources(handlers
    PRIVATE
        src/CommandHandler.cpp
        src/ErrorHandler.cpp
)

target_include_directories(handlers
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(handlers PRIVATE common)
