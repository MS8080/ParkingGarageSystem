/**
 * @file test_io.c
 * @brief Unit tests for the write_report() function in io.c
 */

#include "unity.h"
#include "garage.h"
#include "io.h"
#include <stdio.h>
#include <string.h>



/**
 * @brief Test that write_report creates a report file with expected content.
 */
void test_write_report_creates_file(void) {
    Garage g = {0};

    // Vehicle that has exited
    strcpy(g.vehicles[0].license_plate, "XYZ123");
    g.vehicles[0].entry_time.hour = 10;
    g.vehicles[0].entry_time.minute = 0;
    g.vehicles[0].exit_time.hour = 12;
    g.vehicles[0].exit_time.minute = 0;
    g.vehicles[0].has_exited = 1;

    // Vehicle still inside
    strcpy(g.vehicles[1].license_plate, "ABC999");
    g.vehicles[1].entry_time.hour = 21;
    g.vehicles[1].entry_time.minute = 30;
    g.vehicles[1].has_exited = 0;

    g.count = 2;
    g.total_served = 2;
    g.total_revenue = 4.0;

    const char *report_file = "test_report.txt";
    write_report(&g, report_file);

    FILE *fp = fopen(report_file, "r");
    TEST_ASSERT_NOT_NULL(fp);

    char buffer[512];
    int found_plate1 = 0, found_plate2 = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "XYZ123")) found_plate1 = 1;
        if (strstr(buffer, "ABC999")) found_plate2 = 1;
    }

    fclose(fp);
    TEST_ASSERT_TRUE(found_plate1);
    TEST_ASSERT_TRUE(found_plate2);
}

/**
 * @brief Test that write_report correctly handles an empty garage.
 */
void test_write_report_empty_garage(void) {
    Garage g = {0};
    const char *filename = "test_empty.txt";
    write_report(&g, filename);

    FILE *fp = fopen(filename, "r");
    TEST_ASSERT_NOT_NULL(fp);

    char buffer[512];
    int found_total = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "Total Cars Served: 0")) {
            found_total = 1;
            break;
        }
    }

    fclose(fp);
    TEST_ASSERT_TRUE(found_total);
}

/**
 * @brief Test that write_report lists cars still inside after 22:00.
 */
void test_vehicle_still_inside_after_22(void) {
    Garage g = {0};

    strcpy(g.vehicles[0].license_plate, "LATE88");
    g.vehicles[0].entry_time.hour = 21;
    g.vehicles[0].entry_time.minute = 55;
    g.vehicles[0].has_exited = 0;

    g.count = 1;
    g.total_served = 1;
    g.total_revenue = 0.0;

    const char *filename = "test_late.txt";
    write_report(&g, filename);

    FILE *fp = fopen(filename, "r");
    TEST_ASSERT_NOT_NULL(fp);

    char buffer[512];
    int found = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "LATE88")) {
            found = 1;
            break;
        }
    }

    fclose(fp);
    TEST_ASSERT_TRUE(found);
}

