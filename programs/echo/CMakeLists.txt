set(TARGET_NAME echo)

set(SRC_C
    echo.c
)

set(SRC_H
)

prepend_include(${TARGET_FOLDER_NAME} SRC_H)

add_executable(${TARGET_NAME}
    ${SRC_C}
)    

target_link_libraries(${TARGET_NAME} PRIVATE
    rv32-system
    libnosys
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/tools/memgen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.elf > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.mem
)