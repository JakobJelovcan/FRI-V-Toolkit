set(TARGET_FILES
    ubyte_test.c
    sbyte_test.c
    uhword_test.c
    shword_test.c
    word_test.c
    sbyte_access_test.s
    ubyte_access_test.s
    shword_access_test.s
    uhword_access_test.s
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