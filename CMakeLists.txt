cmake_minimum_required(VERSION 3.28)
project(first)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        first main.cpp
        math/math.h
        math/helpers.cpp
        atomic/atomic.h
        atomic/atomic.cpp
        cluster/cluster.h
        cluster/cluster.cpp
        printer/base.h
        printer/cluster.h
)
