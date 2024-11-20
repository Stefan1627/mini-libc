// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	char *dest_ptr = destination;  // Save the starting address of destination

    while (*source != '\0') {
    	*dest_ptr++ = *source++;
	}
	*dest_ptr = '\0';
	//da
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	// Save the starting address of destination
	char *dest_ptr = destination;
	unsigned long i =  0;

    while (*source != '\0' && i <= len) {
    	*dest_ptr++ = *source++;
		i++;
	}

	*dest_ptr = '\0';

	return destination;
}

char *strcat(char *destination, const char *source)
{
    char *dest_ptr = destination;

    // Move dest_ptr to the end of the current string (at the null terminator)
    while (*dest_ptr != '\0') {
        dest_ptr++;
    }

    while ((*dest_ptr++ = *source++) != '\0'){}

    return destination;
}


char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	char *dest_ptr = destination;
	unsigned long i = 0;
	while (*dest_ptr != '\0') {
		dest_ptr++;
	}

	while (*source != '\0' && i < len) {
		*dest_ptr++ = *source++;
		i++;
	}

	*dest_ptr = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	while (*str1 == *str2) {
		if (*str1 == '\0') {
			return 0;
		}
			str1++;
			str2++;
	}
	if (*str1 < *str2) {
		return -1;
	} else {
			return 1;
		}

	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    while (len > 0) {
        // If we reach a null terminator in either string, stop comparing
        if (*str1 == '\0' || *str2 == '\0') {
            if (*str1 == *str2) {
                return 0;
            } else {
                if ((unsigned char)*str1 < (unsigned char)*str2) {
                    return -1;
                } else {
                    return 1;
                }
            }
        }

        // Compare characters
        if (*str1 != *str2) {
            if ((unsigned char)*str1 < (unsigned char)*str2) {
                return -1;
            } else {
                return 1;
            }
        }

        // Move to the next characters in both strings
        str1++;
        str2++;
        len--;
    }

    // If len reaches zero, strings are equal up to the given length
    return 0;
}



size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	while (*str != '\0') {
		if (*str == c) {
			return (char *)str;
		}
		str++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	size_t len = strlen(str);
	size_t i = len;
	for (; i > 0; i--) {
		if (str[i - 1] == c) {
			return (char *)str + i - 1;
		}
	}
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	size_t len = strlen(needle);
	size_t i = 0;
	size_t j = 0;
	for (; haystack[i] != '\0'; i++) {
		if (haystack[i] == needle[j]) {
			j++;
			if (j == len) {
				return (char *)haystack + i - j + 1;
			}
		} else {
			j = 0;
		}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	size_t len = strlen(needle);
	size_t i = 0;
	size_t j = 0;
	size_t haystack_len = strlen(haystack);
	char *dest_ptr = NULL;
	for (; i < haystack_len; i++) {
		if (haystack[i] == needle[j]) {
			j++;
			if (j == len) {
				dest_ptr = (char *)haystack + i - j + 1;
			}
		} else {
			j = 0;
		}
	}
	return dest_ptr;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	// Cast the source and destination to unsigned char* to handle raw memory copying
    unsigned char *dest_ptr = (unsigned char *)destination;
    const unsigned char *src_ptr = (const unsigned char *)source;

    // Copy num bytes from source to destination
    for (size_t i = 0; i < num; i++) {
        dest_ptr[i] = src_ptr[i];
    }

    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
    unsigned char *dest_ptr = (unsigned char *)destination;
    const unsigned char *src_ptr = (const unsigned char *)source;

    if (dest_ptr < src_ptr) {
        // Copy forwards if there's no overlap or dest is before source
        for (size_t i = 0; i < num; i++) {
            dest_ptr[i] = src_ptr[i];
        }
    } else {
        // Copy backwards if there's overlap and dest is after source
        for (size_t i = num; i > 0; i--) {
            dest_ptr[i - 1] = src_ptr[i - 1];
        }
    }

    return destination;
}


int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	const unsigned char  *ptr1_ptr = (const unsigned char *)ptr1;
	const unsigned char  *ptr2_ptr = (const unsigned char *)ptr2;
	for (size_t i = 0; i < num; i++) {
		if (ptr1_ptr[i] != ptr2_ptr[i]) {
			if(ptr1_ptr[i] < ptr2_ptr[i]) {
				return -1;
			} else {
				return 1;
			}
		}
	}
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	unsigned char *source_ptr = (unsigned char *)source;
	for (size_t i = 0; i < num; i++) {
		source_ptr[i] = (unsigned char)value;
	}
	return source;
}
