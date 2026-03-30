cmake_minimum_required(VERSION 3.16)

project(CDBKVS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/wal.cpp
    src/kv_store.cpp
)

add_library(kvstore ${SOURCES})

target_include_directories(kvstore PUBLIC src)

find_package(Threads REQUIRED)
target_link_libraries(kvstore PRIVATE Threads::Threads)

add_executable(kv_benchmark benchmark/benchmark.cpp)

target_link_libraries(kv_benchmark kvstore)