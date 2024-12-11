set(TARGET_NAME rv32-system)

set(SRC_C
    plic.c
    interrupts.c
    time.c
    uart.c
    uprintf.c
    cache.c
    startup.c
    crt0.s
)

set(SRC_H
    plic.h
    interrupts.h
    time.h
    uart.h
    uprintf.h
    cache.h
    assert.h
)

prepend_include(${TARGET_FOLDER_NAME} SRC_H)

add_library(${TARGET_NAME} OBJECT
    ${SRC_C}
    ${SRC_H}
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_BINARY_DIR}/../include
)