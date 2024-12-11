#include <errno.h>

int readlink(const char* restrict pathname, char* restrict buf, size_t bufsiz) {
    errno = ENOSYS;
    return -1;
}