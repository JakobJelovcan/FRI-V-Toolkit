ENTRY(_start)

MEMORY
{
    rom (irx!aw) : ORIGIN = 0x00000000, LENGTH = 32K
    ram (arw!ix) : ORIGIN = 0x08000000, LENGTH = 128M
}

SECTIONS
{
    __stack_size = DEFINED(__stack_size) ? __stack_size : 0x800;
    PROVIDE(__stack_size = __stack_size);

    __heap_size = DEFINED(__heap_size) ? __heap_size : 0x10000;
    PROVIDE(__heap_size = __heap_size);

    .init : ALIGN(8) {
        KEEP(*(.text.init.start))
    } > rom

    .handlers : ALIGN(8) {
        KEEP(*(.text.interrupts.handlers))
    } > rom

    .interrupt_vector : ALIGN(8) {
        KEEP(*(.text.interrupts.vector))
    } > rom

    .text : ALIGN(8) {
        *(.text)
    } > rom

    .rodata : {
        *(.rdata)
        *(.rodata .rodata.*)
        . = ALIGN(8);
        *(.srodata.cst16)
        *(.srodata.cst8)
        *(.srodata.cst4)
        *(.srodata.cst2)
        *(.srodata .srodata.*)
    } > rom

    .data : ALIGN(8) {
        *(.data .*data.*)
        . = ALIGN(8);
        PROVIDE(__global_pointer$ = . + 0x800);
        *(.sdata .sdata.* .sdata2.*)
    } > ram AT > rom

    PROVIDE(metal_segment_data_source_start = LOADADDR(.data));
    PROVIDE(metal_segment_data_target_start = ADDR(.data));
    PROVIDE(metal_segment_data_target_end = ADDR(.data) + SIZEOF(.data));

    .bss : ALIGN(8) {
        *(.sbss*)
        *(.bss .bss.*)
        *(COMMON)
    } > ram

    PROVIDE(metal_segment_bss_target_start = ADDR(.bss));
    PROVIDE(metal_segment_bss_target_end = ADDR(.bss) + SIZEOF(.bss));

    .stack (NOLOAD) : ALIGN(16) {
        PROVIDE(metal_segment_stack_begin = .);
        . += __stack_size;
        PROVIDE(_sp = .);
        PROVIDE(metal_segment_stack_end = .);
    } > ram

    .heap (NOLOAD) : ALIGN(8) {
        PROVIDE(_end = .);
        PROVIDE(__heap_start = .);
        PROVIDE(metal_segment_heap_start = .);
        . = DEFINED(__heap_max) ? LENGTH(ram) - ( . - ORIGIN(ram)) : __heap_size;
        PROVIDE(metal_segment_heap_end = .);
        PROVIDE(_heap_end = .);
        PROVIDE(__heap_end = .);
    } > ram
}