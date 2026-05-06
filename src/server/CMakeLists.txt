find_package(Boost REQUIRED COMPONENTS system)

add_library(server
    server.cpp session.cpp
)

target_include_directories(server
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(server
    PUBLIC Boost::system
    PUBLIC common
)

add_executable(server_app
    main.cpp
)

target_link_libraries(server_app
    PRIVATE server
)