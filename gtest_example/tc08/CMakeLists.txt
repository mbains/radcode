set(Main_SRCS
    main.c
)

set(MAIN_App
   tc08 
)

link_directories("/opt/picoscope/lib")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -I/opt/picoscope/include/")

add_executable(${MAIN_App}
    ${Main_SRCS}
)


# Specify here the libraries this program depends on
target_link_libraries(${MAIN_App}
usbtc08
)

install(TARGETS ${MAIN_App} DESTINATION bin)

