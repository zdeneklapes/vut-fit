cmake_minimum_required(VERSION 2.8.2)

project(htab_test)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GoogleTest.cmake)

# test targets
enable_testing()

add_executable(${PROJECT_NAME}
        ${PROJECT_NAME}.cpp
#       project files ...
        htab.h
        htab_bucket_count.c
        htab_clear.c
        htab_define.h
        htab_erase.c
        htab_find.c
        htab_for_each.c
        htab_free.c
        htab_hash_function.c
        htab_init.c
        htab_lookup_add.c
        htab_move.c
        htab_size.c
)

target_link_libraries(${PROJECT_NAME} gtest_main)
GTEST_ADD_TESTS(${PROJECT_NAME} "" ${PROJECT_NAME}.cpp)