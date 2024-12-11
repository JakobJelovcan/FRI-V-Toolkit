#include <errno.h>

int _close(int fd) {
    errno = ENOSYS;
    return -1;
}