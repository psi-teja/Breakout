cmake_minimum_required(VERSION 3.15)
project(Breakout VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect sources from src/
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

if(NOT PROJECT_SOURCES)
  message(FATAL_ERROR "No source files found in src/. Add your .cpp/.c files under src/ and re-run CMake.")
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Public include directory (use include/ for headers)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Compiler warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror=return-type)
  endif()
endif()

# Put binaries in bin/
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Optional: try to find and link SDL2 if present
find_package(SDL2 QUIET)
if(SDL2_FOUND)
  message(STATUS "Found SDL2: ${SDL2_INCLUDE_DIRS}")
  target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif()

# Install rule
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)