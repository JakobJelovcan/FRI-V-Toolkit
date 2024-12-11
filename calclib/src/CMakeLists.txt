set(TARGET_NAME calclib)

set(SRC_C
    parse.c
    lex.c
)

set(SRC_H
    parse.h
    lex.h
)

prepend_include(${TARGET_FOLDER_NAME} SRC_H)

add_library(${TARGET_NAME} STATIC
    ${SRC_C}
    ${SRC_H}
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_BINARY_DIR}/../include
)