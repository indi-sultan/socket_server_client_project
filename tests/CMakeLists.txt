enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(runTests test_client_server.cpp)
target_link_libraries(runTests PRIVATE GTest::gtest_main common)  # `common` = your shared lib
add_test(NAME AllTests COMMAND runTests)
