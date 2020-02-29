cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled Server/server.cpp Server/Graph.cpp Server/Graph.h)


add_executable(QtTest Server/server.cpp)