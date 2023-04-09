set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ARM)

if (MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif (UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif ()

string(SUBSTRING "${TOOLCHAIN_PREFIX}" 0 13 TOOLCHAIN)

execute_process(
    COMMAND ${UTIL_SEARCH_CMD} ${TOOLCHAIN_PREFIX}gcc
    OUTPUT_VARIABLE BINUTILS_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (MINGW OR CYGWIN OR WIN32)
    if (BINUTILS_PATH)
        string(REPLACE "\n" ";" BINUTILS_PATH "${BINUTILS_PATH}")
        list(GET BINUTILS_PATH 0 BINUTILS_PATH)
    endif ()
endif ()

if (NOT BINUTILS_PATH)
    message(FATAL_ERROR "ARM GCC toolchain not found")
endif ()

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)

get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)
# Without that flag CMake is not able to pass test compilation check
if (${CMAKE_VERSION} VERSION_EQUAL "3.6.0" OR ${CMAKE_VERSION} VERSION_GREATER "3.6")
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
else ()
    set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")
endif ()

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
# set(CMAKE_AR ${TOOLCHAIN_PREFIX}ar)
# set(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}ranlib)

set(CMAKE_OBJCOPY ${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE_UTIL ${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}size CACHE INTERNAL "size tool")

set(CMAKE_SYSROOT ${ARM_TOOLCHAIN_DIR}/../${TOOLCHAIN})
set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
