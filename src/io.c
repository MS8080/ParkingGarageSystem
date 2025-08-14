//
// Created by Mohamad Sakkal on 14.08.25.
//
#include <stdio.h>
#include "garage.h"
#include "io.h"

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