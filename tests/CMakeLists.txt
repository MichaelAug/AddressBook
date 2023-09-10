# Include main binary headers
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Create test file executable
add_executable(addressBookTests addressBookTests.cpp)

# Link test executable with GTest
target_link_libraries(addressBookTests gtest gtest_main)

# Add the test executable to CTest
add_test(NAME addressBookTests COMMAND addressBookTests)