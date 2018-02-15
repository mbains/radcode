set(Main_SRCS
    main.cpp
)

add_executable(myApp
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(myApp
    libfoo
    libbar
)

install(TARGETS myApp DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Manny Bains") #required
 
INCLUDE(CPack)
