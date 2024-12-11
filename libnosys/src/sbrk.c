#include <errno.h>

void* _sbrk(int incr) {
    extern char _end;
    extern char metal_segment_heap_end;  // Byte at the first address outside of the heap
    static char* heap_end;
    char* prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;
    heap_end += incr;

    if (heap_end > &metal_segment_heap_end) {
        heap_end = prev_heap_end;
        errno = ENOMEM;
        return (void*) -1;
    }

    return (void*) prev_heap_end;
}