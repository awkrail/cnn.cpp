cmake_minimum_required(VERSION 3.14)

project(cnn.cpp VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_subdirectory(ggml)
add_library(cnn SHARED ${LIB_SOURCES})
target_include_directories(cnn PUBLIC include "${CMAKE_SOURCE_DIR}/ggml/include")
target_link_libraries(cnn PUBLIC ggml)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE cnn)
