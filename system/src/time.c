#include <system/time.h>

volatile mtime_t* const mtimer = (mtime_t*) TIMER_BASE;

void mtimer_set_raw_time_cmp(uint64_t offset) {
    const uint64_t new_mtimecmp = mtimer_get_raw_time() + offset;
    mtimer->mtimecmph = 0xFFFFFFFF;
    mtimer->mtimecmpl = (uint32_t) new_mtimecmp;
    mtimer->mtimecmph = (uint32_t) (new_mtimecmp >> 32);
}

uint64_t mtimer_get_raw_time_cmp() {
    return (uint64_t) ((((uint64_t) mtimer->mtimecmph) << 32) | mtimer->mtimecmpl);
}

uint64_t mtimer_get_raw_time() {
    uint32_t mtimel;
    uint32_t mtimeh;
    do {
        mtimeh = mtimer->mtimeh;
        mtimel = mtimer->mtimel;
    } while (mtimeh != mtimer->mtimeh);

    return (uint64_t) ((((uint64_t) mtimeh) << 32) | mtimel);
}

clock_t clock(void) {
    return (clock_t) mtimer_get_raw_time();
}