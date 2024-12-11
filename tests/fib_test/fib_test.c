#include <system/interrupts.h>
#include <system/uart.h>
#include <system/assert.h>

int fib(int n);

int main() {
    assert(fib(0) == 1);
    assert(fib(1) == 1);
    assert(fib(2) == 2);
    assert(fib(6) == 13);
    assert(fib(9) == 55);
    return 0;
}

int fib(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}