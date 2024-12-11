#include <errno.h>
#include <stdlib.h>
#include <system/assert.h>

int main() {
    void* ptr;
    ptr = malloc(sizeof(int) * 1024 * 1024 * 256);
    assert(ptr == NULL);

    ptr = malloc(sizeof(int) * 10);
    assert(ptr != NULL);

    return 0;
}