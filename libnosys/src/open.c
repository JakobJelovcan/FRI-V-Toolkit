#include <errno.h>

int _open(char* file, int flags, int mode) {
    errno = ENOSYS;
    return -1;
}
