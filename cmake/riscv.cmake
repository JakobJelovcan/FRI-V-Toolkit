find_file(RISCV_GCC_COMPILER "riscv32-unknown-elf-gcc" PATHS ENV INCLUDE)

if (NOT EXISTS ${RISCV_GCC_COMPILER})
    message(FATAL_ERROR "RISC-V GCC not found.")
endif()

message("RISC-V GCC found: ${RISCV_GCC_COMPILER}")

get_filename_component(RISCV_TOOLCHAIN_BIN_PATH ${RISCV_GCC_COMPILER} DIRECTORY)
get_filename_component(RISCV_TOOLCHAIN_BIN_GCC ${RISCV_GCC_COMPILER} NAME_WE)
get_filename_component(RISCV_TOOLCHAIN_BIN_EXT ${RISCV_GCC_COMPILER} EXT)

message("RISC-V GCC Path: ${RISCV_TOOLCHAIN_BIN_PATH}")

string(REGEX REPLACE "\-gcc" "-" RISCV_GCC_PREFIX ${RISCV_TOOLCHAIN_BIN_GCC})
message("RISC-V Cross Compile: ${RISCV_GCC_PREFIX}")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR rv32im_zicsr)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_ASM_COMPILER ${RISCV_GCC_PREFIX}gcc)
set(CMAKE_AR_COMPILER ${RISCV_GCC_PREFIX}ar)
set(CMAKE_C_COMPILER ${RISCV_GCC_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${RISCV_GCC_PREFIX}g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -O3 -ffunction-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -O3 -ffunction-sections")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -O3 -ffunction-sections")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXX flags")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}" CACHE STRING "ASM flags")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -march=${CMAKE_SYSTEM_PROCESSOR} -Wl,--no-warn-rwx-segments -ffreestanding -nostartfiles -fno-exceptions -Xlinker -gc-sections -T${LINKER_SCRIPT} -Xlinker --defsym=__heap_max=1 -Xlinker --defsym=__stack_size=0x100000")
