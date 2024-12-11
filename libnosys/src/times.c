#include <errno.h>
#include <sys/times.h>

clock_t _times(struct tms* buf) {
    errno = ENOSYS;
    return -1;
}