cmake_minimum_required(VERSION 3.0)
project(LedController)
set(CMAKE_CXX_STANDARD 11)
# Find raylib package
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(raylib REQUIRED)

# Add your main executable
add_executable(BreakOut main.cpp)
# Link raylib and other required libraries
target_link_libraries(BreakOut PRIVATE raylib)

