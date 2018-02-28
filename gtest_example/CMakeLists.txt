cmake_minimum_required(VERSION 3.10)

project(gtest_example)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

enable_testing()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.0 COMPONENTS system regex asio)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    #add_executable(progname file1.cxx file2.cxx) 
    #target_link_libraries(progname ${Boost_LIBRARIES})
endif()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libfoo)
add_subdirectory(libbar)
add_subdirectory(asio_example)
#add_subdirectory(appupdate)
#add_subdirectory(libos_exec)
#add_subdirectory(installers)

