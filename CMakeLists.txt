cmake_minimum_required(VERSION 3.26)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

# Create a library target
#This command tells CMake to create a static library named bigint using the source file bigint.cpp. The STATIC keyword specifies that the library is a static library.
add_library(bigint STATIC bigint.cpp)

# Create the executable target and link the library
add_executable(lab2 main.cpp)
target_link_libraries(lab2 PRIVATE bigint)