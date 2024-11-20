#include <time.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec req, rem;

    // Set the desired sleep time
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    // Call nanosleep and handle any potential interruptions
    while (nanosleep(&req, &rem) == -1) {
        if (errno == EINTR) {
            // Interrupted by a signal, so continue sleeping for the remaining time
            req = rem;
        } else {
            // Some other error occurred, return the remaining seconds
            return req.tv_sec;
        }
    }

    // Return 0 when the sleep completes successfully
    return 0;
}
