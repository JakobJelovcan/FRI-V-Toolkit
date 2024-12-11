#define assert(E) {       \
    if (!(E)) {           \
        __asm("ebreak");  \
    }                     \
}             
