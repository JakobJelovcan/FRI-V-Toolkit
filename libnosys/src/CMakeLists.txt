set(TARGET_NAME libnosys)

set(SRC_C
    sbrk.c
    open.c
    read.c
    fork.c
    kill.c
    link.c
    stat.c
    wait.c
    write.c
    lseek.c
    fstat.c
    times.c
    unlink.c
    isatty.c
    getpid.c
    close.c
    chown.c
    execve.c
    symlink.c
    gettod.c
    readlink.c
)

set(SRC_H
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