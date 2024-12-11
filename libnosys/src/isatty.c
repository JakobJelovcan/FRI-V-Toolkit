#include <errno.h>

int _isatty(int fd) {
    errno = ENOSYS;
    return -1;
}