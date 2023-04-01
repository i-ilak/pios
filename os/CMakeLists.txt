add_subdirectory(src/common)

# If build with Makefiles, make output verbose.
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${ARCH_DIR}/linker.ld")

set(SOURCES
    src/kernel/uart.c 
    src/kernel/mmio.c 
    src/kernel/kernel.c 
    ${ARCH_DIR}/boot.S
)

# Create minimal ELF binary from sources.
add_executable(${KERNEL}.elf ${SOURCES})

if(${ARCH} STREQUAL "AARCH_32")
    if(${MODEL} STREQUAL "MODEL_0")
        target_compile_definitions(${KERNEL}.elf PUBLIC MODEL_0 AARCH_32)
    elseif(${MODEL} STREQUAL "MODEL_2")
        target_compile_definitions(${KERNEL}.elf PUBLIC MODEL_2 AARCH_32)
    endif()
elseif(${ARCH} STREQUAL "AARCH_64")
    if(${MODEL} STREQUAL "MODEL_3")
        target_compile_definitions(${KERNEL}.elf PUBLIC MODEL_3 AARCH_64)
    elseif(${MODEL} STREQUAL "MODEL_4")
        target_compile_definitions(${KERNEL}.elf PUBLIC MODEL_4 AARCH_64)
    endif()
endif()

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
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${BUILD_DIR}/${KERNEL}.elf ${BUILD_DIR}/${KERNEL}.img
)

# Bind above objcopy custom command with `kernel_img` target.
add_custom_target(kernel_img ALL DEPENDS ${KERNEL}.img)