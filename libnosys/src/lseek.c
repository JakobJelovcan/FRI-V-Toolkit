#include <errno.h>

int _lseek(int fd, int offset, int whence) {
    errno = ENOSYS;
    return -1;
}