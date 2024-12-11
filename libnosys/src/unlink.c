#include <errno.h>

int _unlink(const char* pathname) {
    errno = ENOSYS;
    return -1;
}