#include <unistd.h>
#include <errno.h>

int puts(const char *str)
{
    // Find the length of the input string
    const char *s = str;

    // Loop to find the null terminator
    while (*s) s++;

    // Write the string (excluding the null terminator) to stdout (file descriptor 1)
    if (write(1, str, s - str) == -1) {
        // Return EOF on error
        return -1;
    }

    // Write the newline character to stdout
    if (write(1, "\n", 1) == -1) {
        // Return EOF on error
        return -1;
    }

    return 1;
}
