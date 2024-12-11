#include <errno.h>

int _link(char* oldpath, char* newpath) {
    errno = ENOSYS;
    return -1;
}