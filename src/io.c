/**
* @file io.c
 * @brief Handles file input/output for the Parking Garage Management System.
 *
 * This file contains functions responsible for writing the end-of-day
 * report that includes all served cars, vehicles still inside,
 * total revenue, and total number of cars served.
 *
 * @author
 * Mohamad Sakkal
 * @date 14.08.25
 */

#include <stdio.h>
#include "structs.h"
#include "io.h"

/**
 * @brief Writes the end-of-day parking garage report to a file.
 *
 * This report includes:
 * - A list of all cars that entered and exited with timestamps
 * - The total number of cars served during the day
 * - The total revenue collected
 * - A list of cars still inside the garage at closing time
 *
 * @param g Pointer to the Garage structure
 * @param filename Name of the file to write the report to
 */
void write_report(const Garage *g, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Could not open output file");
        return;
    }

    fprintf(file, "Daily Parking Garage Report\n");
    fprintf(file, "===========================\n\n");

    fprintf(file, "Served Cars:\n");
    for (int i = 0; i < g->count; ++i) {
        Vehicle v = g->vehicles[i];
        if (v.has_exited) {
            fprintf(file, " - %s entered at %02d:%02d, exited at %02d:%02d\n",
                    v.license_plate, v.entry_time.hour, v.entry_time.minute,
                    v.exit_time.hour, v.exit_time.minute);
        }
    }

    fprintf(file, "\nTotal Cars Served: %d\n", g->total_served);
    fprintf(file, "Total Revenue: €%.2f\n", g->total_revenue);

    fprintf(file, "\nVehicles Still Inside:\n");
    for (int i = 0; i < g->count; ++i) {
        if (!g->vehicles[i].has_exited) {
            fprintf(file, " - %s (entered at %02d:%02d)\n",
                    g->vehicles[i].license_plate,
                    g->vehicles[i].entry_time.hour,
                    g->vehicles[i].entry_time.minute);
        }
    }

    fclose(file);
}