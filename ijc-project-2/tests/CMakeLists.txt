cmake_minimum_required(VERSION 2.8.2)
project(ijc_tests)


###############################################################################
#									includes
###############################################################################
include(GoogleTest.cmake)


###############################################################################
#									config
###############################################################################
cmake_minimum_required(VERSION 3.19.2.) # because CLION support max 3.19.2 version
project(main)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)

# cpp preferences
set(CMAKE_CXX_STANDARD 17)                              # This property specifies the C++ standard whose features are requested to build this target.
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)                   # required standart
set(CMAKE_CXX_EXTENSIONS OFF)                           # when ON(default) is used -std=gnu++?? instead of -std=c++??
set(POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")


###############################################################################
#									gtests
###############################################################################
# Test targets
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


###############################################################################
#									bin
###############################################################################
add_executable(htab_test
    htab_test.cpp

# list your htab .c files here
    first_file.c
    second_file.c
# ...
)
target_link_libraries(htab_test gtest_main)
GTEST_ADD_TESTS(htab_test "" htab_test.cpp)
