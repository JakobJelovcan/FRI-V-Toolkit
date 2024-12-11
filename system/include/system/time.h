#pragma once
#include <inttypes.h>
#include <time.h>

#define TIMER_BASE ((void*) 0x10000110)
#define TIMER_MTIME 0x0
#define TIMER_MTIMECMP 0x8

#ifdef CLOCKS_PER_SEC
#undef CLOCKS_PER_SEC
#endif
#define CLOCKS_PER_SEC 50000000  // The clock is running at 50MHz

typedef struct {
    volatile uint32_t mtimel;
    volatile uint32_t mtimeh;
    volatile uint32_t mtimecmpl;
    volatile uint32_t mtimecmph;
} mtime_t;

extern volatile mtime_t* const mtimer;

void mtimer_set_raw_time_cmp(uint64_t offset);
uint64_t mtimer_get_raw_time_cmp();
uint64_t mtimer_get_raw_time();