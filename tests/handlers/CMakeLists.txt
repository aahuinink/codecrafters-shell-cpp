find_package(GTest CONFIG REQUIRED)

add_executable(handlers_tests
        handlers_tests.cpp
)

target_link_libraries(handlers_tests
    PRIVATE
        handlers
        common
        GTest::gtest
        GTest::gtest_main
)
