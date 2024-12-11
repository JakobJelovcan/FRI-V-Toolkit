#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int _fstat(int fd, struct stat* st) {
    errno = ENOSYS;
    return -1;
}