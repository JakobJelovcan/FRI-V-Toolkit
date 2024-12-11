set(TARGET_NAMES
    bypass_test_1
    bypass_test_2
    bypass_test_3
    bypass_test_4
    bypass_test_5
)

set(SRC_C
)

set(SRC_H
)

prepend_include(${TARGET_FOLDER_NAME} SRC_H)

foreach(TARGET_NAME IN LISTS TARGET_NAMES)
    add_executable(${TARGET_NAME}
        ${TARGET_NAME}.s
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