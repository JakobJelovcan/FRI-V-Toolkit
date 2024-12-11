#include <errno.h>

int _execve(char* name, char** argv, char** env) {
    errno = ENOSYS;
    return -1;
}