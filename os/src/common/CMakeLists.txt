add_library(common STATIC string.c stdlib.c)

target_include_directories(common PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)