cmake_minimum_required (VERSION 3.1.2)

project(NoSQLDatabase)

enable_testing()

include_directories(./)
link_directories(./)

find_package(Boost 1.58.0 COMPONENTS system thread timer unit_test_framework) 

include_directories(${Boost_INCLUDE_DIRS}) 

add_executable(NoSQLDatabase main.cpp Connection/Connection.cpp ipc/ipc.cpp Item/Item.cpp KeyValueStore/KeyValueStore.cpp NoSQLStore/NoSQLStore.cpp)
target_link_libraries(NoSQLDatabase ${Boost_LIBRARIES})

add_executable(unitTest tests/NoSQLDataBaseTest.cpp Connection/Connection.cpp ipc/ipc.cpp Item/Item.cpp KeyValueStore/KeyValueStore.cpp NoSQLStore/NoSQLStore.cpp)
target_link_libraries(unitTest ${Boost_LIBRARIES})

add_custom_command(TARGET unitTest POST_BUILD COMMAND unitTest)