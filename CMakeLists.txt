cmake_minimum_required(VERSION 3.15)
project(ParkingGarageSystem C)

# Use the C11 standard
set(CMAKE_C_STANDARD 11)

# Include the directory for custom headers
include_directories(include)

# === Main Executable ===
# Collect all C source files in the src folder
file(GLOB SRC_FILES "src/*.c")

# Create the main executable
add_executable(ParkingGarageSystem ${SRC_FILES})

# === Unit Test Executable ===
# Add Unity + test + required source files manually
add_executable(ParkingGarageTests
        test/test_garage.c
        test/unity.c
        src/garage.c
        src/functions.c
)

# Include headers from both include/ and test/
target_include_directories(ParkingGarageTests PRIVATE include test)
# Enable code coverage flags for tests
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(ParkingGarageTests PRIVATE --coverage)
    target_link_libraries(ParkingGarageTests PRIVATE --coverage)
endif()