#pragma once

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int     memcmp(const void* __restrict destination, const void* __restrict source, size_t size);
void*   memcpy(void* __restrict, const void* __restrict source, size_t size);
void*   memmove(void* __restrict destination, const void* __restrict source, size_t size);
void*   memset(void* destination, int value, size_t size);

size_t strlen(const char* string);

#ifdef __cplusplus
}
#endif
