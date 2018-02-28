set(Main_SRCS
    main.cpp
)

add_executable(asio_example
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(asio_example
    ${Boost_SYSTEM_LIBRARY}
)

install(TARGETS asio_example DESTINATION bin)

