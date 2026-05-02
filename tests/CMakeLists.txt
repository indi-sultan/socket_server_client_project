find_package(Boost REQUIRED COMPONENTS system)
enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(runTests test_client_server.cpp)
target_link_libraries(runTests
    PRIVATE
    GTest::gtest_main
    Boost::system
    common
    server
)

include(GoogleTest)
gtest_discover_tests(runTests)
