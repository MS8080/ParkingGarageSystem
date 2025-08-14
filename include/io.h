//
// Created by Mohamad Sakkal on 14.08.25.
//
#ifndef IO_H
#define IO_H

#include "structs.h"

/// @file io.h
/// @brief Contains file input/output functions

/// @brief Writes the end-of-day report to a file
/// @param g Pointer to Garage
/// @param filename Name of the output file
void write_report(const Garage *g, const char *filename);

#endif //IO_HKINGGARAGESYSTEM_IO_H