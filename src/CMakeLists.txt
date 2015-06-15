cmake_minimum_required (VERSION 3.1.2)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 11)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED true)

add_subdirectory(Connection)
add_subdirectory(Item)
add_subdirectory(KeyValueStore)
add_subdirectory(NoSQLStore)
add_subdirectory(ipc)
