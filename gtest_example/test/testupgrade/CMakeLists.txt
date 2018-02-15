FIND_PACKAGE(JSONCPP REQUIRED)
FIND_PACKAGE(JSONRPCCPP REQUIRED)
FIND_PACKAGE(CURL REQUIRED)
FIND_PACKAGE(Boost 1.61.0 REQUIRED COMPONENTS system regex filesystem)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})


file(GLOB SRCS *.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ADD_EXECUTABLE(testupgrade ${SRCS})

TARGET_LINK_LIBRARIES(testupgrade
    appupdate
    os_exec
    gtest
    gmock
    jsonrpccpp-server
    jsonrpccpp-client
    jsoncpp
    curl
)

add_test(NAME test_appupdate COMMAND  test_appupdate)

install(TARGETS testupgrade DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Manny Bains") #required
 
INCLUDE(CPack)
