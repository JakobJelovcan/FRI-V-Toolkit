cmake_minimum_required(VERSION 3.25)
set(REPO_NAME RISC-V-Toolkit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MESSAGE_CONTEXT ${REPO_NAME})
set(CMAKE_MESSAGE_CONTEXT_SHOW ON CACHE BOOL "Show CMake message context")

if (CMAKE_FOLDER)
    set(CMAKE_FOLDER ${CMAKE_FOLDER}/${REPO_NAME})
else()
    set(CMAKE_FOLDER ${REPO_NAME})
endif()

option(BUILD_TESTS "Build tests" ON)
option(BUILD_BENCH "Build benchmarks" ON)
option(BUILD_PROGRAMS "Build programs" ON)
option(BUILD_CALCLIB "Build calclib" ON)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(DIRECTORY PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set_property(DIRECTORY PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set_property(DIRECTORY PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

project(${REPO_NAME}
    LANGUAGES CXX ASM C
    VERSION 1.0.0
)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)
include(cmake/utils.cmake)
include(cmake/riscv.cmake)

add_subdirectory(system)
add_subdirectory(libnosys)
add_subdirectory(calclib)
add_subdirectory(tests)
add_subdirectory(benchmarks)
add_subdirectory(programs)