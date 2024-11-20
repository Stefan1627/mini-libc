// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
    /* TODO: Implement open(). */
    va_list args;
    mode_t mode = 0;
    int fd;

    if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    fd = syscall(__NR_open, filename, flags, mode);

    if (fd < 0) {
        errno = -fd;
        return -1;
    }

    return fd;
}
