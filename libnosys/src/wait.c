#include <errno.h>

int _wait(int* wstatus) {
    errno = ENOSYS;
    return -1;
}