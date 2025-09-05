# Parking Garage Management System

A C-based terminal application to simulate and manage a public parking garage with a 100-vehicle capacity.

---

## Features

- Register car **entry** with timestamp and license plate
- Register car **exit** and calculate fee (2€/hour, rounded up)
- Show current **occupancy** and remaining spots
- **Edit** or **correct** entry/exit timestamps
- Block entry when the garage is full
- Generate an **end-of-day report** file with:
  - All cars that entered and exited
  - Total number of cars served
  - Total revenue collected
  - Cars still inside after 22:00

---

## Testing and Coverage

- Unit-tested using the **Unity framework**
- Additional edge-case tests added for:
  - `calculate_duration()` edge cases (zero, partial, overnight)
  - `update_entry_time()` and `update_exit_time()` failure scenarios
  - `print_occupancy()` and `list_unexited()` output verification
- **Test coverage** measured using `gcovr`

---

## Build Instructions

### Prerequisites

- CLion (or any CMake-compatible C compiler)
- `gcovr` (optional, for coverage reports)

### Run the Application

```bash
cmake -B build
cmake --build build
./build/ParkingGarageSystem