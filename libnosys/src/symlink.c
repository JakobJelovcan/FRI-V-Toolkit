#include <errno.h>

int _symlink(const char* target, const char* linkpath) {
    errno = ENOSYS;
    return -1;
}