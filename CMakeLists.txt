cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(DivideAndConquer_ParallelFramework VERSION 1.0
        DESCRIPTION "Third assignment"
        LANGUAGES CXX)

# find package needed by the project
find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# different build requires different flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -fsanitize=thread -fstack-check -fstack-protector-strong -fno-omit-frame-pointer -g -DDEBUG -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-pthread -O3")


add_executable(DivideAndConquer_ParallelFramework main.cpp DCFramework.hpp MergeSort.hpp)
# add_library(master_worker STATIC MasterWorker.hpp)

# set compiler
target_compile_features(DivideAndConquer_ParallelFramework PUBLIC cxx_std_17)
# target_compile_features(master_worker PUBLIC cxx_std_17)

# set_target_properties(master_worker PROPERTIES LINKER_LANGUAGE CXX)

# link libraries
# target_link_libraries(finding_primes master_worker)
target_link_libraries(Threads::Threads)