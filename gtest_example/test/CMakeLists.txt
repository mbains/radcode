find_package(Threads REQUIRED)
set(GMOCK_ROOT "googletest"
    CACHE PATH "The path to the Google test framework.")

# Google Mock & Test
###############################################################################
add_subdirectory(${GMOCK_ROOT})
include_directories(${GMOCK_ROOT}/googlemock/include)
include_directories(${GMOCK_ROOT}/googletest/include)

add_subdirectory(testfoo)
#add_subdirectory(testupgrade)
