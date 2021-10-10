cmake_minimum_required(VERSION 3.21)
project(Thread_1)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.6.0) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

set(Lib lib/embedding.cc lib/instruction.cc lib/utils.cc lib/model.cc)

set(Targets q0 q1 q2 q3)
foreach(target IN LISTS Targets)
    add_executable(${target} ${Lib} ${target}.cc)
endforeach()
