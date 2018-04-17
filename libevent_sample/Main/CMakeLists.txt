
cmake_minimum_required(VERSION 3.10)

set(Main_App main)
set(Main_SRCS
    main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings -O0 -ggdb")

add_executable(${Main_App}
    ${Main_SRCS}
)

target_link_libraries(${Main_App}
    event
)
