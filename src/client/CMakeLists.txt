add_executable(client 
main.cpp
)

target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(client PRIVATE common)