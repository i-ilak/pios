set(CMAKE_C_COMPILER "clang")

add_executable(test test.c)

target_link_libraries(test PRIVATE cmocka)
target_link_directories(test PRIVATE "/opt/homebrew/Cellar/cmocka/1.1.7/lib")
target_include_directories(test PRIVATE "/opt/homebrew/Cellar/cmocka/1.1.7/include")