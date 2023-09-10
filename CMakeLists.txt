cmake_minimum_required(VERSION 3.14)
project(address_book LANGUAGES CXX)

set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Generate compile_commands.json for clang
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

# Find all source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Find all header files
file(GLOB_RECURSE HEADER_FILES inc/*.hpp)

# Add the executable and specify source files
add_executable(${BINARY} ${SRC_FILES} ${HEADER_FILES})

# Define include directories for the binary
target_include_directories(${BINARY} PRIVATE inc)

# Look for an installed Google Test package
find_package(GTest)
if(GTest_FOUND)
    enable_testing()
    add_subdirectory(tests)
else()
    message(WARNING "Google Test not found. Tests will not be built.")
endif()

# Add a custom command to move compile_commands.json after the build
add_custom_command(TARGET ${BINARY}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Moving compile_commands.json to source directory"
)