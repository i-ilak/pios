cmake_minimum_required (VERSION 3.17)

include(cmake/target.cmake)
setup("MODEL_1" ${CMAKE_CURRENT_SOURCE_DIR})
message("Build Info:\n\t - Arch:\t${ARCH}\n\t - Model:\t${MODEL}")
add_compile_options(-DUART_MODE=1) # Activate special mode where charater output gets redirected to UART_0

set(CMAKE_DEPENDS_USE_COMPILER ON)

enable_language(C ASM)

project(piOS VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(os)
