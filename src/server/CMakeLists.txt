add_executable(server 
main.cpp server.cpp
)

# Find Boost libraries (header-only + system)
find_package(Boost REQUIRED COMPONENTS system)

# Link Boost::system (needed by Asio)
target_link_libraries(server PRIVATE Boost::system)


target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(server PRIVATE common)