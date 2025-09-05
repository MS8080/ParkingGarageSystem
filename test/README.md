# test/

This folder contains unit tests and the Unity testing framework for the Parking Garage Management System.

## Unit Test Files

- **test_functions.c**  
  Tests helper logic in `functions.c`, including:
    - Time parsing (`parse_time`)
    - Duration calculation (`calculate_duration`)

- **test_garage.c**  
  Covers core parking logic from `garage.c`, including:
    - Registering vehicle entries
    - Logging exits
    - Occupancy tracking
    - Entry/exit validation

- **test_garage_extra.c**  
  Contains additional and edge-case tests for `garage.c`, including:
    - Cross-hour and overnight exit scenarios
    - Handling vehicles not found in the system
    - Empty garage edge conditions

- **test_io.c**  
  Tests the output functionality in `io.c`, including:
    - Daily report generation
    - Correct listing of served and unserved vehicles
    - Revenue and count calculations

## Framework

- **unity.c / unity.h / unity_internals.h**  
  The [Unity Test Framework](https://github.com/ThrowTheSwitch/Unity), a lightweight unit test framework for C.  
  Used to define and run assertions across test files.

---

To run all tests:
- Build the project using `cmake --build . --target ParkingGarageTests`
- Run the test executable: `./ParkingGarageTests`

Coverage reports are generated using `gcovr`.