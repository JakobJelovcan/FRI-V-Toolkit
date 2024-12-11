#include <errno.h>

int _write(int fd, const void* buf, size_t count) {
    errno = ENOSYS;
    return -1;
}