# Include main library headers
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Create test file executable
add_executable(addressBookTests addressBookTests.cpp)

# Link test executable with GTest
target_link_libraries(addressBookTests GTest::GTest GTest::Main)

# Link main library to test executable
target_link_libraries(addressBookTests ${LIBRARY})

# Add the test executable to CTest
add_test(NAME addressBookTests COMMAND addressBookTests)