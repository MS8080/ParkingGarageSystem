//
// Created by Mohamad Sakkal on 14.08.25.
//
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

/// @file functions.h
/// @brief Contains helper functions for time and input handling

/// @brief Parses a time string in HH:MM format into a Time struct
/// @param str Time string
/// @return Parsed Time
Time parse_time(const char *str);

/// @brief Calculates the duration between two times (rounded up to full hours)
/// @param entry Entry time
/// @param exit Exit time
/// @return Duration in hours
int calculate_duration(Time entry, Time exit);

#endif //FUNCTIONS_Hf //PARKINGGARAGESYSTEM_FUNCTIONS_H