add_executable(client 
main.cpp client.cpp
)
find_package(Boost REQUIRED COMPONENTS system)
target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(client PRIVATE 
    Boost::system
    common
)