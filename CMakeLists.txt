cmake_minimum_required(VERSION 3.10)

project(Breakout)

# Expand source file glob so CMake gets real file names
file(GLOB SOURCES "src/*.cpp")

add_executable(Breakout ${SOURCES})

# Find and link Raylib
find_package(raylib REQUIRED)
target_link_libraries(Breakout raylib)

# Include your source directory
target_include_directories(Breakout PRIVATE src)

# Set C++ standard
set_target_properties(Breakout PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)