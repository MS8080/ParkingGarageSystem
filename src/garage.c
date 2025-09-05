/**
 * @file garage.c
 * @brief Implements the core garage logic including entry, exit, correction, and occupancy tracking.
 *
 * This file handles the primary operations of the Parking Garage Management System,
 * such as registering vehicles, logging exits, calculating fees, correcting timestamps,
 * and displaying garage occupancy.
 *
 * @author
 * Mohamad Sakkal
 * @date 14.08.25
 */


#include <stdio.h>
#include <string.h>
#include "garage.h"

/**
 * @brief Initializes the garage state.
 *
 * Sets all counters (number of vehicles, total served, total revenue) to zero.
 *
 * @param g Pointer to the Garage structure to initialize
 */
void init_garage(Garage *g) {
    g->count = 0;
    g->total_served = 0;
    g->total_revenue = 0.0;
}

/**
 * @brief Registers a new vehicle entry if the garage is not full.
 *
 * Stores the license plate and entry time in the garage data structure.
 *
 * @param g Pointer to the Garage structure
 * @param plate License plate of the vehicle
 * @param time Time of entry
 * @return 0 if the vehicle was successfully registered, -1 if the garage is full
 */
int register_entry(Garage *g, const char *plate, Time time) {
    if (g->count >= 100) return -1;

    strcpy(g->vehicles[g->count].license_plate, plate);
    g->vehicles[g->count].entry_time = time;
    g->vehicles[g->count].has_exited = 0;
    g->count++;
    g->total_served++;
    return 0;
}

/**
 * @brief Logs the exit of a vehicle and calculates the parking fee.
 *
 * Searches for the vehicle using its license plate and records the exit time.
 * The fee is calculated as 2 euros per hour (rounded up).
 *
 * @param g Pointer to the Garage structure
 * @param plate License plate of the vehicle
 * @param time Time of exit
 * @return The calculated fee if successful, -1 if the vehicle is not found or already exited
 */
int log_exit(Garage *g, const char *plate, Time time) {
    for (int i = 0; i < g->count; ++i) {
        if (strcmp(g->vehicles[i].license_plate, plate) == 0 && g->vehicles[i].has_exited == 0) {
            g->vehicles[i].exit_time = time;
            g->vehicles[i].has_exited = 1;

            int hours = time.hour - g->vehicles[i].entry_time.hour;
            if (time.minute > g->vehicles[i].entry_time.minute) hours++;
            g->total_revenue += hours * 2;
            return hours * 2;
        }
    }
    return -1;
}

/**
 * @brief Prints a list of all vehicles currently in the garage.
 *
 * Iterates through all vehicles and prints the ones that have not exited.
 * Also shows a summary of the number of cars inside and remaining spots.
 *
 * @param g Pointer to the Garage structure
 */
void print_occupancy(const Garage *g) {
    int current_inside = 0;

    printf("Current Occupancy:\n");
    for (int i = 0; i < g->count; ++i) {
        if (!g->vehicles[i].has_exited) {
            printf(" - %s (entered at %02d:%02d)\n",
                   g->vehicles[i].license_plate,
                   g->vehicles[i].entry_time.hour,
                   g->vehicles[i].entry_time.minute);
            current_inside++;
        }
    }

    int spots_left = 100 - current_inside;
    printf("\n  %d cars currently parked, %d spots left.\n", current_inside, spots_left);
}

/**
 * @brief Prints a list of all vehicles still inside the garage after closing.
 *
 * This is used in the daily report to identify cars that did not exit by 22:00.
 *
 * @param g Pointer to the Garage structure
 */
void list_unexited(const Garage *g) {
    printf("Vehicles still inside at closing time:\n");
    for (int i = 0; i < g->count; ++i) {
        if (!g->vehicles[i].has_exited) {
            printf(" - %s\n", g->vehicles[i].license_plate);
        }
    }
}

/**
 * @brief Updates the entry time of a vehicle.
 *
 * Allows correction of mistakenly entered timestamps.
 *
 * @param g Pointer to the Garage structure
 * @param plate License plate of the vehicle
 * @param new_time Corrected entry time
 * @return 0 if successful, -1 if vehicle was not found
 */
int update_entry_time(Garage *g, const char *plate, Time new_time) {
    for (int i = 0; i < g->count; ++i) {
        if (strcmp(g->vehicles[i].license_plate, plate) == 0) {
            g->vehicles[i].entry_time = new_time;
            return 0;
        }
    }
    return -1;
}

/**
 * @brief Updates the exit time of a vehicle.
 *
 * Only applicable to vehicles that have already exited.
 *
 * @param g Pointer to the Garage structure
 * @param plate License plate of the vehicle
 * @param new_time Corrected exit time
 * @return 0 if successful, -1 if vehicle is not found or has not exited yet
 */
int update_exit_time(Garage *g, const char *plate, Time new_time) {
    for (int i = 0; i < g->count; ++i) {
        if (strcmp(g->vehicles[i].license_plate, plate) == 0 && g->vehicles[i].has_exited) {
            g->vehicles[i].exit_time = new_time;
            return 0;
        }
    }
    return -1;
}