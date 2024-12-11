#include <errno.h>

int _read(int fd, char* ptr, int len) {
    errno = ENOSYS;
    return -1;
}