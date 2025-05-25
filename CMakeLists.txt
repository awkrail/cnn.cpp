cmake_minimum_required(VERSION 3.14)

project(cnn.cpp VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

file(GLOB LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_subdirectory(ggml)
add_executable(nougat ${LIB_SOURCES})

target_include_directories(nougat
  PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/ggml/include"
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(nougat
  PRIVATE
  ggml
  ${OpenCV_LIBS} 
)
