//
// Created by Mohamad Sakkal on 14.08.25.
//
#include <stdio.h>
#include <string.h>
#include "garage.h"
#include "functions.h"
#include "io.h"

int main() {
    Garage g;
    init_garage(&g);

    int running = 1;
    while (running) {
        printf("\n=== Parking Garage System ===\n");
        printf("1. Register Entry\n");
        printf("2. Log Exit\n");
        printf("3. View Occupancy\n");
        printf("4. End Day & Generate Report\n");
        printf("5. Exit\n");
        printf("Choose option: ");

        int choice;
        scanf("%d", &choice);
        getchar(); // remove newline

        char plate[20], time_str[6];
        Time t;

        switch (choice) {
            case 1:
                printf("License Plate: ");
                fgets(plate, sizeof(plate), stdin);
                plate[strcspn(plate, "\n")] = '\0'; // strip newline

                printf("Entry Time (HH:MM): ");
                fgets(time_str, sizeof(time_str), stdin);
                t = parse_time(time_str);

                if (register_entry(&g, plate, t) == 0)
                    printf("Entry registered.\n");
                else
                    printf("Garage is full!\n");
                break;

            case 2:
                printf("License Plate: ");
                fgets(plate, sizeof(plate), stdin);
                plate[strcspn(plate, "\n")] = '\0';

                printf("Exit Time (HH:MM): ");
                fgets(time_str, sizeof(time_str), stdin);
                t = parse_time(time_str);

                int fee = log_exit(&g, plate, t);
                if (fee >= 0)
                    printf("Exit logged. Fee: €%d\n", fee);
                else
                    printf("Vehicle not found or already exited.\n");
                break;

            case 3:
                print_occupancy(&g);
                break;

            case 4:
                write_report(&g, "daily_report.txt");
                printf("Report written to 'daily_report.txt'.\n");
                break;

            case 5:
                running = 0;
                break;
                printf("6. Correct Entry/Exit Time\n");

                // inside switch:
            case 6:
                printf("License Plate: ");
                fgets(plate, sizeof(plate), stdin);
                plate[strcspn(plate, "\n")] = '\0';

                printf("Correct (1) Entry or (2) Exit time? ");
                int subchoice;
                scanf("%d", &subchoice);
                getchar();

                printf("New Time (HH:MM): ");
                fgets(time_str, sizeof(time_str), stdin);
                t = parse_time(time_str);

                if (subchoice == 1) {
                    if (update_entry_time(&g, plate, t) == 0)
                        printf("Entry time updated.\n");
                    else
                        printf("Vehicle not found.\n");
                } else if (subchoice == 2) {
                    if (update_exit_time(&g, plate, t) == 0)
                        printf("Exit time updated.\n");
                    else
                        printf("Vehicle not found or has not exited.\n");
                } else {
                    printf("Invalid option.\n");
                }
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}