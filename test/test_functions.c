/**
 * @file test_functions.c
 * @brief Unit tests for helper functions in functions.c, including parse_time() and calculate_duration()
 */

#include "unity.h"
#include "functions.h"
#include "structs.h"
#include <string.h>

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


/**
 * @brief Test that a valid time string is parsed correctly.
 */
void test_parse_time_valid(void) {
    Time t = {0};
    t = parse_time("09:30");

    TEST_ASSERT_EQUAL_INT(9, t.hour);
    TEST_ASSERT_EQUAL_INT(30, t.minute);
}

/**
 * @brief Test that midnight time is parsed correctly.
 */
void test_parse_time_midnight(void) {
    Time t = parse_time("00:00");

    TEST_ASSERT_EQUAL_INT(0, t.hour);
    TEST_ASSERT_EQUAL_INT(0, t.minute);
}

/**
 * @brief Test that a time string with max boundary is parsed correctly.
 */
void test_parse_time_boundary(void) {
    Time t = parse_time("23:59");

    TEST_ASSERT_EQUAL_INT(23, t.hour);
    TEST_ASSERT_EQUAL_INT(59, t.minute);
}

/**
 * @brief Test calculate_duration when exit is later on same hour.
 */
void test_calculate_duration_same_hour_round_up(void) {
    Time entry = {10, 0};
    Time exit = {10, 30};
    int duration = calculate_duration(entry, exit);

    TEST_ASSERT_EQUAL_INT(1, duration);
}

/**
 * @brief Test calculate_duration for multi-hour difference.
 */
void test_calculate_duration_multiple_hours(void) {
    Time entry = {9, 15};
    Time exit = {12, 10};
    int duration = calculate_duration(entry, exit);

    TEST_ASSERT_EQUAL_INT(3, duration);
}

/**
 * @brief Test calculate_duration when exit is before entry (overnight wrap).
 */
void test_calculate_duration_wraparound(void) {
    Time entry = {23, 0};
    Time exit = {1, 0};
    int duration = calculate_duration(entry, exit);

    TEST_ASSERT_EQUAL_INT(2, duration);
}


/**
 * @brief Test when entry and exit are the same — should return 0.
 */
void test_calculate_duration_zero(void) {
    Time entry = {10, 0};
    Time exit = {10, 0};
    int result = calculate_duration(entry, exit);
    TEST_ASSERT_EQUAL_INT(0, result);
}

/**
 * @brief Test rounding up when minutes are over — should round up to 1 hour.
 */
void test_calculate_duration_partial_round_up(void) {
    Time entry = {10, 0};
    Time exit = {10, 1};
    int result = calculate_duration(entry, exit);
    TEST_ASSERT_EQUAL_INT(1, result);
}

/**
 * @brief Test a regular case (2-hour difference).
 */
void test_calculate_duration_normal(void) {
    Time entry = {10, 0};
    Time exit = {12, 0};
    int result = calculate_duration(entry, exit);
    TEST_ASSERT_EQUAL_INT(2, result);
}

/**
 * @brief Test wrap-around (overnight) scenario — e.g., entry 23:00, exit 01:00.
 */
void test_calculate_duration_wrap_around(void) {
    Time entry = {23, 0};
    Time exit = {1, 0};
    int result = calculate_duration(entry, exit);
    TEST_ASSERT_EQUAL_INT(2, result);  // 2 hours: 23 → 24 → 1
}

