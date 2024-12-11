#include <string.h>

void init_memory() {
    extern char metal_segment_data_target_start;
    extern char metal_segment_data_source_start;
    extern char metal_segment_data_target_end;
    extern char metal_segment_bss_target_start;
    extern char metal_segment_bss_target_end;

    // Copy data section from rom to ram
    memcpy(&metal_segment_data_target_start,
           &metal_segment_data_source_start,
           &metal_segment_data_target_end - &metal_segment_data_target_start);

    // Set bss section to 0
    memset(&metal_segment_bss_target_start, 0, &metal_segment_bss_target_end - &metal_segment_bss_target_start);
}