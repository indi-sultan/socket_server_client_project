cmake_minimum_required(VERSION 3.28.3)
project(SocketProject LANGUAGES CXX)

#use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#put all compiled binaries into single folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#add subdirectories
add_subdirectory(src/common)
add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(tests)