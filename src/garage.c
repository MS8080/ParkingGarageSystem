//
// Created by Mohamad Sakkal on 14.08.25.
//
#include <stdio.h>
#include <string.h>
#include "garage.h"

void init_garage(Garage *g) {
    g->count = 0;
    g->total_served = 0;
    g->total_revenue = 0.0;
}

int register_entry(Garage *g, const char *plate, Time time) {
    if (g->count >= 100) return -1;

    strcpy(g->vehicles[g->count].license_plate, plate);
    g->vehicles[g->count].entry_time = time;
    g->vehicles[g->count].has_exited = 0;
    g->count++;
    g->total_served++;
    return 0;
}

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

void print_occupancy(const Garage *g) {
    printf("Current Occupancy:\n");
    for (int i = 0; i < g->count; ++i) {
        if (!g->vehicles[i].has_exited) {
            printf(" - %s (entered at %02d:%02d)\n", g->vehicles[i].license_plate,
                   g->vehicles[i].entry_time.hour, g->vehicles[i].entry_time.minute);
        }
    }
}

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
 * Searches for a vehicle by license plate and sets a new entry time.
 *
 * @param g Pointer to the garage
 * @param plate License plate string
 * @param new_time New entry time
 * @return 0 if successful, -1 if vehicle not found
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
 * Only works if the vehicle has already exited.
 *
 * @param g Pointer to the garage
 * @param plate License plate string
 * @param new_time New exit time
 * @return 0 if successful, -1 if vehicle not found or has not exited
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