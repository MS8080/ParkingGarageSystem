#ifndef STRUCTS_H
#define STRUCTS_H

/// @file structs.h
/// @brief Contains data structures used throughout the parking garage system

/// @brief Structure for representing a time (HH:MM)
typedef struct {
    int hour;   ///< Hour component (0-23)
    int minute; ///< Minute component (0-59)
} Time;

/// @brief Structure for representing a parked vehicle
typedef struct {
    char license_plate[20]; ///< License plate number
    Time entry_time;        ///< Time of vehicle entry
    Time exit_time;         ///< Time of vehicle exit
    int has_exited;         ///< Flag to check if the vehicle exited (1 = yes, 0 = no)
} Vehicle;

/// @brief Structure for the parking garage
typedef struct {
    Vehicle vehicles[100];  ///< Fixed-size array for 100 vehicles max
    int count;              ///< Current number of vehicles in the garage
    int total_served;       ///< Total number of vehicles served during the day
    double total_revenue;   ///< Total revenue generated
} Garage;

#endif //STRUCTS_HUCTS_H