cmake_minimum_required (VERSION 3.1.2)

add_executable(ipc ipc.cpp)
set_property(TARGET ipc PROPERTY CXX_STANDARD 11)
set_property(TARGET ipc PROPERTY CXX_STANDARD_REQUIRED true)
