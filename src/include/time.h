#ifndef TIME_H
#define TIME_H

#include <internal/syscall.h>
#include <stddef.h>

struct timespec {
    time_t tv_sec;  // Seconds
    long   tv_nsec; // Nanoseconds
};

struct tm {
    int tm_sec;   // Seconds (0-60)
    int tm_min;   // Minutes (0-59)
    int tm_hour;  // Hours (0-23)
    int tm_mday;  // Day of the month (1-31)
    int tm_mon;   // Month (0-11, where January = 0)
    int tm_year;  // Year since 1900
    int tm_wday;  // Day of the week (0-6, where Sunday = 0)
    int tm_yday;  // Day of the year (0-365)
    int tm_isdst; // Daylight saving time flag
};

// Function prototypes
int nanosleep(const struct timespec *req, struct timespec *rem);
unsigned int sleep(unsigned int seconds);

#define CLOCKS_PER_SEC  1000000000L  // Number of clock ticks per second

#endif // TIME_H
