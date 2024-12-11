#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>

int _gettimeofday(struct timeval* ptimeval, void* ptimezone) {
    errno = ENOSYS;
    return -1;
}