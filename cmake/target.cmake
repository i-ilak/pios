macro(setup model path)
    set(BUILD_DIR ${path}/build/bin)

    if(${model} STREQUAL "MODEL_0")
        set(CPU arm1176jzf-s)
        set(ARCH_DIR ${path}/arch/armv6)
    elseif(${model} STREQUAL "MODEL_2")
        set(CPU cortex-a7)
        set(ARCH_DIR ${path}/arch/armv7-a)
    elseif(${model} STREQUAL "MODEL_3")
        set(ARCH_DIR ${path}/arch/armv8-a)
        set(CPU cortex-a53)
    elseif(${model} STREQUAL "MODEL_4")
        set(ARCH_DIR ${path}/arch/armv8-a)
        set(CPU cortex-a72)
    endif()

    if(${model} STREQUAL "MODEL_0"
        OR ${model} STREQUAL "MODEL_2")
        setup_arch("32")
    else()
        setup_arch("64")
    endif()

    set(MODEL ${model})

endmacro()

macro(setup_arch arch)
    if(${arch} STREQUAL "32")
        set(ARCH "AARCH_32")
        set(TOOLCHAIN_PREFIX arm-none-eabi-)
        set(KERNEL kernel7)
    else()
        set(ARCH "AARCH_64")
        set(TOOLCHAIN_PREFIX aarch64-none-elf-)
        set(KERNEL kernel8)
    endif()

    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake")

endmacro()
