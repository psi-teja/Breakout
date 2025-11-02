cmake_minimum_required(VERSION 3.10)

project(Breakout)

# Expand source file glob so CMake gets real file names
file(GLOB SOURCES "src/*.cpp")

add_executable(Breakout ${SOURCES})