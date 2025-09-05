cmake_minimum_required(VERSION 3.15)
project(ParkingGarageSystem C)

# Use the C11 standard
set(CMAKE_C_STANDARD 11)

# === Include directories ===
include_directories(include test)

# === Main app sources ===
file(GLOB SRC_FILES "src/*.c")

# === Main executable ===
add_executable(ParkingGarageSystem ${SRC_FILES})

# === Unit test executable ===
add_executable(ParkingGarageTests
        test/test_garage.c
        test/unity.c
        src/garage.c
        src/functions.c
)

# === Optional: Code coverage flags ===
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(ParkingGarageTests PRIVATE --coverage)
    target_link_libraries(ParkingGarageTests PRIVATE --coverage)
endif()