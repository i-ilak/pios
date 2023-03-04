set(KERNEL kernel7)
set(CPU arm1176jzf-s)

# If build with Makefiles, make output verbose.
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/../arch/armv6/linker.ld")

# Create minimal ELF binary from sources.
add_executable(${KERNEL}.elf src/kernel/kernel.c ../arch/armv6/boot.S)

# The compiler must make no assumptions about the build.
set_target_properties(${KERNEL}.elf PROPERTIES LINK_FLAGS "-nostdlib -nostartfiles")
set_target_properties(${KERNEL}.elf PROPERTIES COMPILE_FLAGS "-mcpu=${CPU} -Wall -O2 -ffreestanding -nostdlib -nostartfiles" )

# Need to add the utils library
# target_link_libraries(${KERNEL}.elf PRIVATE utils)

# Generates the binary with objcopy.
add_custom_command(
    OUTPUT ${KERNEL}.img
    DEPENDS ${KERNEL}.elf
    COMMENT "objcopy -O binary kernel7.elf kernel7.img"
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin/${KERNEL}.elf ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin/${KERNEL}.img
)

# Bind above objcopy custom command with `minimal_bin` target.
add_custom_target(kernel_img ALL DEPENDS ${KERNEL}.img)
