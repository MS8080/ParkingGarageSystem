#  Parking Garage Management System

A C-based terminal application to manage a public parking garage with 100-vehicle capacity, open daily from 06:00 to 22:00.

---

##  Features

- Register car **entry** with timestamp and license plate
- Register car **exit** and calculate fee (2€/hour, rounded up)
- Show current **occupancy**
- **Edit/correct** entry or exit timestamps
- **Block entry** if garage is full
- Generate end-of-day **report file** with:
    - All cars that entered and exited
    - Total number of cars served
    - Total revenue
    - Cars still inside after 22:00
- **Unit-tested** using [Unity](https://github.com/ThrowTheSwitch/Unity)
- Test coverage report using `gcovr`

---

##  Build Instructions

###  Prerequisites

- CLion or any CMake-based C compiler
- `gcovr` (optional, for test coverage)

###  Run Main Application

```bash
cmake -B build
cmake --build build
./build/ParkingGarageSystem