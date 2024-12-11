set(TARGET_NAME coremark)

set(SRC_C
    core_list_join.c
    core_main.c
    core_matrix.c
    core_portme.c
    core_state.c
    core_util.c
    cvt.c
    ee_printf.c
)

add_executable(${TARGET_NAME}
    ${SRC_C}
)    

target_link_libraries(${TARGET_NAME} PRIVATE
    rv32-system
    libnosys
)

add_compile_definitions(FLAGS_STR="${CMAKE_C_FLAGS}")
add_compile_definitions(ITERATIONS=0)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/tools/memgen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.elf > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.mem
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker --defsym=__heap_max=1 -Xlinker --defsym=__stack_size=0x100000")
