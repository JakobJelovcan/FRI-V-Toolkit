#include <stdint.h>
#include <system/cache.h>

void flush_cache(const void* from, const void* to) {
    for (char* volatile ptr = (char* volatile) (((uintptr_t) from) & -4); ptr < (char*) to; ptr += 16)
        *ptr;
}