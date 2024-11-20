// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#define MIN_ALLOC_SIZE 4096  // Minimum allocation size (4KB)
#define PAGE_SIZE 4096       // System page size
#define SIZE_MAX 18446744073709551615ULL


void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	// Ensure size is at least the minimum allocation size
    size_t alloc_size;

    if (size < MIN_ALLOC_SIZE) {
        alloc_size = MIN_ALLOC_SIZE;
    } else {
        alloc_size = size;
    }

    // Allocate memory using mmap()
    void *ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        return NULL;
    }

    // Add the allocated block to the memory tracking list
    if (mem_list_add(ptr, alloc_size) < 0) {
        // If adding to the memory list fails, free the allocated memory
        munmap(ptr, alloc_size);
        return NULL;
    }

    return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	// Calculate the total size needed
    size_t total_size = nmemb * size;

    // Check for multiplication overflow
    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;
    }

    // Use malloc to allocate the memory
    void *ptr = malloc(total_size);
    if (ptr == NULL) {
        return NULL;
    }

    // Initialize the allocated memory to zero
    memset(ptr, 0, total_size);

    return ptr;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
    // Check if the pointer is NULL
    if (ptr == NULL) {
        return;
    }

    // Find the allocated block in the memory tracking list
    struct mem_list *item = mem_list_find(ptr);
    if (item == NULL) {
        // The memory was not found in the list, possibly invalid pointer
        return;
    }

    // Free the allocated memory using munmap, using the length of the memory block
    munmap(ptr, item->len);

    // Remove the allocated block from the memory tracking list
    if (mem_list_del(ptr) < 0) {
        // If removing from the memory list fails, do nothing
        return;
    }

    return;
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
    // Check if the pointer is NULL, which means we need to allocate new memory
    if (ptr == NULL) {
        return malloc(size);
        }
        // Check if the size is zero, which means we need to free the memory
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // Find the memory block in the list
    struct mem_list *item = mem_list_find(ptr);
    if (item == NULL) {
        // If the pointer is not found in the list, it is not a valid block to real
        return NULL;
    }

    // Check if the new size is larger than the current size
    if (size > item->len) {
        // If the new size is larger, we need to allocate new memory
        void *new_ptr = malloc(size);
        if (new_ptr == NULL) {
            return NULL;
        }
        // Copy the data from the old memory block to the new memory block
        memcpy(new_ptr, ptr, item->len);
        // Free the old memory block
        free(ptr);
        return new_ptr;
    } else if (size < item->len) {
        // If the new size is smaller, we need to truncate the memory block
        void *new_ptr = malloc(size);
        if (new_ptr == NULL) {
            return NULL;
        }
        // Copy the data from the old memory block to the new memory block
        memcpy(new_ptr, ptr, size);
        // Free the old memory block
        free(ptr);
        return new_ptr;
    }

    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
    // Check for overflow in the multiplication of nmemb and size.
    if (nmemb && size > SIZE_MAX / nmemb) {
        return NULL;
    }

    size_t total_size = nmemb * size;

    // If ptr is NULL, this behaves like malloc.
    void *new_ptr = realloc(ptr, total_size);

    if (new_ptr == NULL) {
        return NULL;
    }

    return new_ptr;
}
