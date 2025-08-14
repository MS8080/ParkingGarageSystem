//
// Created by Mohamad Sakkal on 14.08.25.
//
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

Time parse_time(const char *str) {
    Time t;
    sscanf(str, "%d:%d", &t.hour, &t.minute);
    return t;
}

int calculate_duration(Time entry, Time exit) {
    int start_minutes = entry.hour * 60 + entry.minute;
    int end_minutes = exit.hour * 60 + exit.minute;
    int diff = end_minutes - start_minutes;
    if (diff <= 0) return 0;
    return (diff + 59) / 60; // Round up
}