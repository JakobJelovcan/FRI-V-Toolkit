#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int _stat(const char* restrict pathname, struct stat* restrict statbuf) {
    errno = ENOSYS;
    return -1;
}