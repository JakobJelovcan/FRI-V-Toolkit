# FRI-V-Toolkit

Repository containing the tools required for compiling test programs for the FRI-V cpu.

## Requirements
 - gcc-riscv32 toolchain available at https://github.com/stnolting/riscv-gcc-prebuilt

## Building programs
 - `$ mkdir build && cd build`
 - `$ cmake ..`
 - `$ cmake --build . --config Release`

## Running programs

In order to run the program copy the contents of the *.mem file into the rom.mem file within the FRI-V project and run the simulation.

## Testing

Success of the test is determined by the result of the main function (0 indicates success).

## Aditional

If required you can modify the the size of the stack and heap by defining linker flags `-Xlinker --defsym=__stack_size=0x800`, `-Xlinker --defsym=__heap_size=0x800`.
By default the stack is 1MiB in size and the heap uses all of the available memory.
These flags are defined in `cmake/riscv.cmake`.

The FRI-V cpu has a 32KiB rom and a 128MiB ram.
