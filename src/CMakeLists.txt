cmake_minimum_required (VERSION 3.1.2)

project(NoSQLDatabase)

include_directories(./)
link_directories(./)

find_package(Boost 1.58.0 COMPONENTS system thread timer) 

include_directories(${Boost_INCLUDE_DIRS}) 

add_executable(NoSQLDatabase main.cpp Connection/Connection.cpp ipc/ipc.cpp Item/Item.cpp KeyValueStore/KeyValueStore.cpp NoSQLStore/NoSQLStore.cpp)
target_link_libraries(NoSQLDatabase ${Boost_LIBRARIES})
