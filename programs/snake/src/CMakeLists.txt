set(TARGET_NAME snake)

set(SRC_C
    snake.c
    game.c
)

set(SRC_H
    snake.h
)

prepend_include(${TARGET_FOLDER_NAME} SRC_H)

add_executable(${TARGET_NAME}
    ${SRC_C}
    ${SRC_H}
)    

target_link_libraries(${TARGET_NAME} PRIVATE
    rv32-system
    libnosys
    m
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_BINARY_DIR}/../include
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/tools/memgen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.elf > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.mem
)