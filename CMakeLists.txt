cmake_minimum_required(VERSION 3.16)
project(ParkingGarageSystem C)

set(CMAKE_C_STANDARD 11)

# Include header directories
include_directories(include)
include_directories(test)

# ============================
# 📁 Source Groups
# ============================

# Logic source files (used in both app and tests)
set(LOGIC_FILES
        src/garage.c
        src/functions.c
        src/io.c
)

# Header files (useful for IDEs)
set(HEADER_FILES
        include/garage.h
        include/functions.h
        include/io.h
        include/structs.h
)

# Main app (with main function)
set(APP_MAIN
        src/main.c
)

# Test files
set(TEST_FILES
        test/test_garage.c
        test/test_io.c
        test/test_functions.c
        test/unity.c
        test/test_garage_extra.c
)

#  Executables

# Main application executable
add_executable(ParkingGarageSystem
        ${APP_MAIN}
        ${LOGIC_FILES}
        ${HEADER_FILES}
)

# Unit test executable (excludes main.c)
add_executable(ParkingGarageTests
        ${TEST_FILES}
        ${LOGIC_FILES}
        ${HEADER_FILES}
)

# Enable Testing


enable_testing()
add_test(NAME ParkingGarageTests COMMAND ParkingGarageTests)


# Code Coverage Flags


foreach(target ParkingGarageSystem ParkingGarageTests)
    target_compile_options(${target} PRIVATE -g -O0 --coverage)
    target_link_options(${target} PRIVATE --coverage)
endforeach()