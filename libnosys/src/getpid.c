#include <errno.h>

int _getpid() {
    errno = ENOSYS;
    return -1;
}