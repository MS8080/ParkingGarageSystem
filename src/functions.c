/**
* @file functions.c
 * @brief Implements helper functions for time parsing and duration calculation.
 *
 * These functions are used to support the main logic in the Parking Garage Management System,
 * such as converting string-based times and calculating time differences for fee computation.
 *
 * @author
 * Mohamad Sakkal
 * @date 14.08.25
 */


#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/**
 * @brief Parses a time string in the format "HH:MM" into a Time struct.
 *
 * This function converts a string input into hour and minute values.
 *
 * @param str The input time string in "HH:MM" format
 * @return Time struct containing hour and minute fields
 */
Time parse_time(const char *str) {
    Time t;
    sscanf(str, "%d:%d", &t.hour, &t.minute);
    return t;
}

/**
 * @brief Calculates the duration between two times, rounded up to full hours.
 *
 * Computes the number of hours (rounded up) between the given entry and exit times.
 * Used to determine the parking fee.
 *
 * @param entry Entry time
 * @param exit Exit time
 * @return Duration in hours (minimum 0)
 */
int calculate_duration(Time entry, Time exit) {
    int start_minutes = entry.hour * 60 + entry.minute;
    int end_minutes   = exit.hour * 60 + exit.minute;
    int diff = end_minutes - start_minutes;

    if (diff < 0) {
        // Wrap-around for overnight parking
        diff += 24 * 60;
    } else if (diff == 0) {
        // Same time → duration is zero
        return 0;
    }

    // Round up to the next full hour
    return (diff + 59) / 60;
}