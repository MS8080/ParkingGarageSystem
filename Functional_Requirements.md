# Functional Requirements – Parking Garage Management System

## FR1: Vehicle Entry Registration
The system shall allow the parking attendant to register a new vehicle entry by entering the license plate number and the current timestamp, only if the total number of vehicles in the garage is less than 100.

- **Reason:** To handle new entries and respect the garage’s capacity.
- **Testable:** Yes, by simulating a full garage and checking that entry is denied.

---

## FR2: Vehicle Exit Logging and Fee Calculation
The system shall allow the parking attendant to manually log a vehicle’s exit by entering the license plate and current timestamp. The system shall calculate the fee as €2 per full or partial hour and update the vehicle record accordingly.

- **Reason:** To compute correct fees and allow exit tracking.
- **Testable:** Yes, by providing entry/exit times and verifying the calculated fee.

---

## FR3: Occupancy Display
The system shall display the current number of vehicles inside the garage and list their license plates, when requested by the parking attendant.

- **Reason:** Enables attendants to know how many and which vehicles are currently inside.
- **Testable:** Yes, by asserting garage state after multiple entries/exits.

---

## FR4: Correction of Entry or Exit Times
The system shall allow the parking attendant to update a previously logged entry or exit time for a vehicle, by entering the license plate number and the new timestamp.

- **Reason:** For error correction (e.g., wrong time input).
- **Testable:** Yes, by modifying and validating the corrected time and recalculated fee.

---

## FR5: Full Garage Handling
The system shall prevent new vehicle entries once the garage reaches 100 parked vehicles, and display an appropriate message to the parking attendant.

- **Reason:** To enforce the fixed garage capacity.
- **Testable:** Yes, by registering 100 entries and attempting a 101st.

---

## FR6: Daily Output File Generation
At the end of the day, the system shall generate an output file that includes:
- a list of all cars that entered and exited,
- the total number of cars served,
- the total revenue,
- and a list of cars that entered but did not exit before 22:00.

- **Reason:** For end-of-day reporting and accountability.
- **Testable:** Yes, by generating and parsing the output file.
