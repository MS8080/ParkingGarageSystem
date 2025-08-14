//
// Created by Mohamad Sakkal on 14.08.25.
//
#ifndef GARAGE_H
#define GARAGE_H

#include "structs.h"

/// @file garage.h
/// @brief Contains functions for managing vehicle entry, exit, and garage state

/// @brief Initializes the garage structure
/// @param g Pointer to Garage
void init_garage(Garage *g);

/// @brief Registers a vehicle entering the garage
/// @param g Pointer to Garage
/// @param plate License plate
/// @param time Entry time
/// @return 0 if success, -1 if garage is full
int register_entry(Garage *g, const char *plate, Time time);

/// @brief Logs the exit of a vehicle and calculates the fee
/// @param g Pointer to Garage
/// @param plate License plate
/// @param time Exit time
/// @return Fee if success, -1 if vehicle not found or already exited
int log_exit(Garage *g, const char *plate, Time time);

/// @brief Prints the current occupancy
/// @param g Pointer to Garage
void print_occupancy(const Garage *g);

/// @brief Lists cars that have not exited by closing time
/// @param g Pointer to Garage
void list_unexited(const Garage *g);

/// @brief Update the entry time of a vehicle
/// @param g Pointer to Garage
/// @param plate License plate to search for
/// @param new_time New entry time
/// @return 0 if success, -1 if vehicle not found
int update_entry_time(Garage *g, const char *plate, Time new_time);

/// @brief Update the exit time of a vehicle
/// @param g Pointer to Garage
/// @param plate License plate to search for
/// @param new_time New exit time
/// @return 0 if success, -1 if vehicle not found or not yet exited
int update_exit_time(Garage *g, const char *plate, Time new_time);

#endif //GARAGE_HARAGESYSTEM_GARAGE_H