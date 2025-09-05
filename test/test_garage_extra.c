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

/**
 * @brief Test print_occupancy() output
 *
 * Captures stdout into a buffer and checks if the expected license plate appears.
 */
void test_print_occupancy_output(void) {
    Garage g = {0};
    strcpy(g.vehicles[0].license_plate, "TEST1");
    g.vehicles[0].entry_time.hour = 10;
    g.vehicles[0].entry_time.minute = 30;
    g.vehicles[0].has_exited = 0;
    g.count = 1;

    char buffer[256];
    FILE *original_stdout = stdout;
    FILE *temp = fmemopen(buffer, sizeof(buffer), "w");
    stdout = temp;

    print_occupancy(&g);
    fflush(temp);
    fclose(temp);
    stdout = original_stdout;

    TEST_ASSERT(strstr(buffer, "TEST1") != NULL);
}

/**
 * @brief Test list_unexited() output
 *
 * Captures stdout into a buffer and checks if the expected license plate appears.
 */
void test_list_unexited_output(void) {
    Garage g = {0};
    strcpy(g.vehicles[0].license_plate, "TEST2");
    g.vehicles[0].entry_time.hour = 9;
    g.vehicles[0].entry_time.minute = 45;
    g.vehicles[0].has_exited = 0;
    g.count = 1;

    char buffer[256];
    FILE *original_stdout = stdout;
    FILE *temp = fmemopen(buffer, sizeof(buffer), "w");
    stdout = temp;

    list_unexited(&g);
    fflush(temp);
    fclose(temp);
    stdout = original_stdout;

    TEST_ASSERT(strstr(buffer, "TEST2") != NULL);
}

/**
 * @brief Test combination scenario:
 * Register a car, log exit, then immediately update times.
 */
void test_register_exit_update_times(void) {
    Garage g = {0};
    Time entry = {8, 0};
    Time exit_old = {10, 0};
    Time exit_new = {11, 15};
    Time entry_new = {7, 45};

    // Register car
    int result = register_entry(&g, "COMBO1", entry);
    TEST_ASSERT_EQUAL_INT(0, result);

    // Log exit
    int fee = log_exit(&g, "COMBO1", exit_old);
    TEST_ASSERT_EQUAL_INT(4, fee); // 2 hours × €2

    // Update entry time (should succeed)
    result = update_entry_time(&g, "COMBO1", entry_new);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(7, g.vehicles[0].entry_time.hour);
    TEST_ASSERT_EQUAL_INT(45, g.vehicles[0].entry_time.minute);

    // Update exit time (should succeed)
    result = update_exit_time(&g, "COMBO1", exit_new);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(11, g.vehicles[0].exit_time.hour);
    TEST_ASSERT_EQUAL_INT(15, g.vehicles[0].exit_time.minute);
}

/// @brief Tests update_entry_time() for a vehicle that does not exist
void test_update_entry_time_vehicle_not_found(void) {
    Garage g = {0};
    Time t = {10, 0};
    int result = update_entry_time(&g, "NONEXISTENT", t);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

/// @brief Tests update_exit_time() for a vehicle that hasn’t exited
void test_update_exit_time_vehicle_not_exited(void) {
    Garage g = {0};
    Time entry = {8, 0};
    register_entry(&g, "CAR123", entry);
    Time new_exit = {10, 0};
    int result = update_exit_time(&g, "CAR123", new_exit);
    TEST_ASSERT_EQUAL_INT(-1, result);
}

/// @brief Tests fee calculation when exit minutes are before entry minutes (cross-hour)
void test_log_exit_cross_hour(void) {
    Garage g = {0};
    Time entry = {9, 50};
    Time exit = {10, 10};
    register_entry(&g, "CROSS1", entry);
    int fee = log_exit(&g, "CROSS1", exit); // should round up to 1 hour × €2
    TEST_ASSERT_EQUAL_INT(2, fee);
}

/**
 * @brief Test log_exit() when exit minutes < entry minutes (cross-hour rounding)
 */
void test_log_exit_minutes_before_entry(void) {
    Garage g = {0};
    Time entry = {10, 30};
    Time exit_time = {11, 0}; // exit minutes < entry minutes to test rounding
    register_entry(&g, "BRANCH1", entry);

    int fee = log_exit(&g, "BRANCH1", exit_time);
    // Duration 30 min → rounds up to 1 hour × €2
    TEST_ASSERT_EQUAL_INT(2, fee);
}

/**
 * @brief Test print_occupancy() with empty garage
 */
void test_print_occupancy_empty(void) {
    Garage g = {0};
    // Should execute without crash
    print_occupancy(&g);
}

/**
 * @brief Test list_unexited() with empty garage
 */
void test_list_unexited_empty(void) {
    Garage g = {0};
    list_unexited(&g);
}

/**
 * @brief Test log_exit() for a vehicle that does not exist
 */
void test_log_exit_vehicle_not_found(void) {
    Garage g = {0};
    Time exit = {10, 0};
    int fee = log_exit(&g, "NONEXIST", exit);
    TEST_ASSERT_EQUAL_INT(-1, fee);
}

