// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	/* TODO: Implement mmap(). */

	if ((flags & MAP_ANONYMOUS) && fd != -1) {
		// Invalid fd when MAP_ANONYMOUS is set
        errno = EBADF;
        return MAP_FAILED;
    } else if (!(flags & MAP_ANONYMOUS) && fd < 0) {
		// Invalid fd when MAP_ANONYMOUS is not set
        errno = EBADF;
        return MAP_FAILED;
    }

    // Check that at least one of MAP_PRIVATE or MAP_SHARED is set
    if (!(flags & MAP_PRIVATE) && !(flags & MAP_SHARED)) {
		// Invalid flags combination
        errno = EINVAL;
        return MAP_FAILED;
    }

    // Invoke the mmap syscall using a syscall wrapper
    long result = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if (result < 0) {
		errno = -result;
        return MAP_FAILED;
    }

    return (void *)result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	void *result = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);
	if (result == MAP_FAILED) {
		return MAP_FAILED;
	}
	return result;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	int result = syscall(__NR_munmap, addr, length);
	if (result < 0) {
		errno = -result;
		return -1;
	}
	return result;
}
