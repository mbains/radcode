cmake_minimum_required(VERSION 3.10)

project(gtest_example)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libfoo)
add_subdirectory(libbar)
#add_subdirectory(appupdate)
#add_subdirectory(libos_exec)
#add_subdirectory(installers)

