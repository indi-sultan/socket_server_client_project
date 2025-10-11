add_library(common STATIC utils.cpp)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/include)
