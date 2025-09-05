//
// Created by Mohamad Sakkal on 14.08.25.
//
/**
 * @file test_garage.c
 * @brief Unit tests for the Parking Garage System using the Unity framework
 *
 * This file tests core garage functionalities:
 * - Vehicle entry registration
 * - Vehicle exit and fee calculation
 * - Time duration calculation with rounding
 */

#include "unity.h"
#include "../include/garage.h"
#include "../include/functions.h"

// Declarations for external tests
void test_update_entry_time_not_found(void);
void test_update_exit_time_not_found(void);
void test_update_exit_time_not_exited(void);
void test_print_occupancy(void);
void test_list_unexited(void);

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
void test_print_occupancy_output(void);
void test_list_unexited_output(void);
void test_register_exit_update_times(void);


/// @brief Global Garage object used across all test cases
Garage g;

/**
 * @brief Setup function called before each test
 *
 * Initializes the garage to an empty state.
 */
void setUp(void) {
    init_garage(&g);
}

/**
 * @brief Teardown function called after each test
 *
 * Currently unused.
 */
void tearDown(void) {
    // Nothing to clean up
}

/**
 * @test Tests whether a vehicle can be registered correctly
 */
void test_register_entry(void) {
    Time t = {8, 30};
    int result = register_entry(&g, "ABC123", t);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("ABC123", g.vehicles[0].license_plate);
    TEST_ASSERT_EQUAL_INT(8, g.vehicles[0].entry_time.hour);
    TEST_ASSERT_EQUAL_INT(30, g.vehicles[0].entry_time.minute);
}

/**
 * @test Tests whether the system correctly logs a vehicle exit and calculates the parking fee
 */
void test_log_exit_and_fee(void) {
    Time in = {10, 0};
    Time out = {12, 15};
    register_entry(&g, "XYZ789", in);
    int fee = log_exit(&g, "XYZ789", out);
    // 2 hours and 15 minutes = 3 full hours × €2 = €6
    TEST_ASSERT_EQUAL_INT(6, fee);
}

/**
 * @test Tests whether duration calculation correctly rounds up partial hours
 */
void test_calculate_duration_round_up(void) {
    Time in = {9, 0};
    Time out = {10, 1}; // 61 minutes => should round up to 2 hours
    int duration = calculate_duration(in, out);
    TEST_ASSERT_EQUAL_INT(2, duration);
}

/**
 * @brief Main test runner
 *
 * Initializes Unity and runs all test functions.
 *
 * @return int Unity test summary result
 */
/**
 * @test
 * @brief Tests whether the entry time of a vehicle can be updated using update_entry_time().
 *
 * This test registers a vehicle, then updates its entry time and verifies
 * that the entry time is correctly overwritten.
 */
void test_update_entry_time(void) {
    Time old_time = {9, 0};
    Time new_time = {10, 15};
    register_entry(&g, "COR123", old_time);

    int result = update_entry_time(&g, "COR123", new_time);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(10, g.vehicles[0].entry_time.hour);
    TEST_ASSERT_EQUAL_INT(15, g.vehicles[0].entry_time.minute);
}

/**
 * @test
 * @brief Tests whether the exit time of a vehicle can be updated using update_exit_time().
 *
 * This test logs an exit for a vehicle and then updates the exit time.
 * It verifies that the updated exit time is applied.
 */
void test_update_exit_time(void) {
    Time in = {8, 0};
    Time out_old = {10, 0};
    Time out_new = {12, 30};

    register_entry(&g, "EXIT123", in);
    log_exit(&g, "EXIT123", out_old);

    int result = update_exit_time(&g, "EXIT123", out_new);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(12, g.vehicles[0].exit_time.hour);
    TEST_ASSERT_EQUAL_INT(30, g.vehicles[0].exit_time.minute);
}

/**
 * @test
 * @brief Tests whether the garage prevents registering more than 100 vehicles.
 *
 * This test fills the garage to maximum capacity, then attempts to
 * register one additional vehicle, which should fail with -1.
 */
void test_garage_capacity_limit(void) {
    Time t = {7, 0};
    for (int i = 0; i < 100; ++i) {
        char plate[10];
        snprintf(plate, sizeof(plate), "CAR%03d", i);
        int result = register_entry(&g, plate, t);
        TEST_ASSERT_EQUAL_INT(0, result);
    }

    int overflow = register_entry(&g, "OVERFLOW", t);
    TEST_ASSERT_EQUAL_INT(-1, overflow);
}

/**
 * @test
 * @brief Tests that logging an exit twice is not allowed.
 *
 * This test logs an exit once (should return a fee), then attempts to log the exit again,
 * which should fail with a return value of -1.
 */
void test_double_exit_disallowed(void) {
    Time in = {9, 0};
    Time out = {10, 0};

    register_entry(&g, "DUPE123", in);
    int fee1 = log_exit(&g, "DUPE123", out);
    int fee2 = log_exit(&g, "DUPE123", out); // second attempt

    TEST_ASSERT_EQUAL_INT(2, fee1);   // 1 hour × €2
    TEST_ASSERT_EQUAL_INT(-1, fee2);  // should be disallowed
}


int main(void) {
    UNITY_BEGIN();

    // Original test_garage.c tests
    RUN_TEST(test_register_entry);
    RUN_TEST(test_log_exit_and_fee);
    RUN_TEST(test_calculate_duration_round_up);
    RUN_TEST(test_update_entry_time);
    RUN_TEST(test_update_exit_time);
    RUN_TEST(test_garage_capacity_limit);
    RUN_TEST(test_double_exit_disallowed);

    // From test_io.c
    RUN_TEST(test_write_report_creates_file);
    RUN_TEST(test_write_report_empty_garage);
    RUN_TEST(test_vehicle_still_inside_after_22);

    // From test_functions.c
    RUN_TEST(test_parse_time_valid);
    RUN_TEST(test_parse_time_midnight);
    RUN_TEST(test_parse_time_boundary);
    RUN_TEST(test_calculate_duration_zero);
    RUN_TEST(test_calculate_duration_partial_round_up);
    RUN_TEST(test_calculate_duration_normal);
    RUN_TEST(test_calculate_duration_wrap_around);

    //from test_garage_extra.c
    RUN_TEST(test_update_entry_time_not_found);
    RUN_TEST(test_update_exit_time_not_found);
    RUN_TEST(test_update_exit_time_not_exited);
    RUN_TEST(test_print_occupancy);
    RUN_TEST(test_list_unexited);
    RUN_TEST(test_print_occupancy_output);
    RUN_TEST(test_list_unexited_output);
    RUN_TEST(test_register_exit_update_times);

    return UNITY_END();

}