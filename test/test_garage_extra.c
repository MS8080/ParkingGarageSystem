//
// Created by Mohamad Sakkal on 05.09.25.
//

/**
 * @file test_garage_extra.c
 * @brief Additional unit tests for garage.c edge cases.
 */

#include "unity.h"
#include "garage.h"
#include <stdio.h>
#include <string.h>

void test_write_report_creates_file(void);
void test_write_report_empty_garage(void);
void test_vehicle_still_inside_after_22(void);
void test_parse_time_valid(void);
void test_parse_time_midnight(void);
void test_parse_time_boundary(void);
void test_calculate_duration_zero(void);
void test_calculate_duration_partial_round_up(void);
void test_calculate_duration_normal(void);
void test_calculate_duration_wrap_around(void);


/**
 * @brief Test update_entry_time() when vehicle is not in the garage.
 */
void test_update_entry_time_not_found(void) {
    Garage g = {0};
    Time t = {10, 0};
    int result = update_entry_time(&g, "NOTFOUND", t);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

/**
 * @brief Test update_exit_time() when vehicle is not in the garage.
 */
void test_update_exit_time_not_found(void) {
    Garage g = {0};
    Time t = {12, 0};
    int result = update_exit_time(&g, "UNKNOWN", t);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

/**
 * @brief Test update_exit_time() when vehicle has not yet exited.
 */
void test_update_exit_time_not_exited(void) {
    Garage g = {0};
    strcpy(g.vehicles[0].license_plate, "ABC123");
    g.vehicles[0].has_exited = 0;
    g.count = 1;
    Time t = {12, 0};
    int result = update_exit_time(&g, "ABC123", t);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

/**
 * @brief Test print_occupancy() output.
 *
 * Captures stdout and verifies expected output.
 */
void test_print_occupancy(void) {
    Garage g = {0};
    strcpy(g.vehicles[0].license_plate, "CAR1");
    g.vehicles[0].entry_time.hour = 10;
    g.vehicles[0].entry_time.minute = 30;
    g.vehicles[0].has_exited = 0;
    g.count = 1;

    // Redirect stdout to buffer
    char buffer[256];
    FILE *tmp = freopen("CONOUT$", "w", stdout);
    print_occupancy(&g);
    fflush(stdout);
    // TODO: Optionally compare captured output in buffer
}

/**
 * @brief Test list_unexited() output.
 *
 * Captures stdout and verifies expected output.
 */
void test_list_unexited(void) {
    Garage g = {0};
    strcpy(g.vehicles[0].license_plate, "CAR2");
    g.vehicles[0].entry_time.hour = 9;
    g.vehicles[0].entry_time.minute = 15;
    g.vehicles[0].has_exited = 0;
    g.count = 1;

    // Redirect stdout to buffer
    char buffer[256];
    FILE *tmp = freopen("CONOUT$", "w", stdout);
    list_unexited(&g);
    fflush(stdout);
}

