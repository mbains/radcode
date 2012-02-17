project(foo)

set(foo_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/foo/foo_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/foo/math_wrapper.cpp
)

set(foo_INCLUDE_DIRECTORIES
    ${SHIBOKEN_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${PYSIDE_INCLUDE_DIR}
    ${PYSIDE_INCLUDE_DIR}/QtCore
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${LIBFOO_DIR}
)

set(foo_LINK_LIBRARIES
    ${QT_QTCORE_LIBRARY}
    ${SHIBOKEN_PYTHON_LIBRARIES}
    ${SHIBOKEN_LIBRARY}
    ${PYSIDE_LIBRARY}
    ${LIBFOO_DIR}/libfoo${CMAKE_SHARED_LIBRARY_SUFFIX}
)

include_directories(foo ${foo_INCLUDE_DIRECTORIES})
add_library(foo MODULE ${foo_SRC})
set_property(TARGET foo PROPERTY PREFIX "")
target_link_libraries(foo ${foo_LINK_LIBRARIES})

if(WIN32)
    set(PATH_SEP ";")
else()
    set(PATH_SEP ":")
endif()

add_custom_command(OUTPUT ${foo_SRC}
                   COMMAND ${GENERATOR}
                   --generatorSet=shiboken
                   --enable-parent-ctor-heuristic
                   --enable-pyside-extensions
                   --enable-return-value-heuristic
                   ${CMAKE_SOURCE_DIR}/foo/global.h
                   --include-paths=${QT_INCLUDE_DIR}${PATH_SEP}${LIBFOO_DIR}
                   --typesystem-paths=${typesystem_path}${PATH_SEP}${PYSIDE_TYPESYSTEMS}
                   --output-directory=${CMAKE_CURRENT_BINARY_DIR}
                   ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_foo.xml
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Running generator for libfoo..."
)

