set(TARGET_FILES
    store_access_fault_test.c
    store_address_misaligned_test.c
    load_access_fault_test.c
    load_address_misaligned_test.c
    instruction_access_fault_test.c
    instruction_address_misaligned_test.c
    illegal_instruction_test.c
    breakpoint_test.c
    machine_system_call_test.c
    software_interrupt_test.s
    rom_access_fault_test.c
    plic_access_fault_test.c
    uart_access_fault_test.c
    timer_access_fault_test.c
    disabled_software_interrupt_test.s
    disabled_timer_interrupt_test.s
    disabled_external_interrupt_test.s
    direct_software_interrupt_test.s
    direct_external_interrupt_test.s
    direct_timer_interrupt_test.s
)

set(SRC_C
)

set(SRC_H
)

prepend_include(${TARGET_FOLDER_NAME} SRC_H)

foreach(TARGET_FILE IN LISTS TARGET_FILES)
    get_filename_component(TARGET_NAME ${TARGET_FILE} NAME_WE)
    add_executable(${TARGET_NAME}
        ${TARGET_FILE}
        ${SRC_C}
    )    

    target_link_libraries(${TARGET_NAME} PRIVATE
        rv32-system
        libnosys
    )

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
       COMMAND ${CMAKE_SOURCE_DIR}/tools/memgen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.elf > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.mem
    )
endforeach()