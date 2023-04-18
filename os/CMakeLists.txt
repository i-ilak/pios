add_subdirectory(src/common)

# If build with Makefiles, make output verbose.
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${ARCH_DIR}/linker.ld")

set(SOURCES
    src/kernel/kerio.c
    src/kernel/gpu.c
    src/kernel/mailbox.c
    src/kernel/framebuffer.c
    src/kernel/memory.c
    src/kernel/atag.c
    src/kernel/uart.c 
    src/kernel/mmio.c 
    src/kernel/kernel.c 
    ${ARCH_DIR}/boot.S
)

# Create minimal ELF binary from sources.
add_executable(${KERNEL}.elf ${SOURCES})

# The compiler must make no assumptions about the build.
set_target_properties(${KERNEL}.elf PROPERTIES LINK_FLAGS "-nostdlib -nostartfiles")
set_target_properties(${KERNEL}.elf PROPERTIES COMPILE_FLAGS "-mcpu=${CPU} -Wall -O2 -ffreestanding -nostdlib -nostartfiles")

# Need to add the utils library
target_include_directories(${KERNEL}.elf PUBLIC include)
target_link_libraries(${KERNEL}.elf PRIVATE common)
# target_link_libraries(${KERNEL}.elf PRIVATE utils)

# Generates the binary with objcopy.
add_custom_command(
    OUTPUT ${KERNEL}.img
    DEPENDS ${KERNEL}.elf
    COMMENT "Creating IMG-file form ELF-file"
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_DIR}/${KERNEL}.elf ${BUILD_DIR}/${KERNEL}.img  && mv ${BUILD_DIR}/${KERNEL}.img ${PROJECT_SOURCE_DIR}/export/
)

# Bind above objcopy custom command with `kernel_img` target.
add_custom_target(kernel_img ALL DEPENDS ${KERNEL}.img)