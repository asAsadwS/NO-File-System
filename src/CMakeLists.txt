set (NOFS_VERSION_MAJOR 0)
set (NOFS_VERSION_MINOR 0)
set (NOFS_VERSION_PATCH 0)
set (NOFS_VERSION ${NOFS_VERSION_MAJOR}.${NOFS_VERSION_MINOR}.${NOFS_VERSION_PATCH})

set (TIMESTAMP G_COMPILE_TIME %y%m%d)

set (SRC_LIST config.c nofs.cpp blockl.cpp logl.cpp)
set (HEADER_LIST ${PROJECT_BINARY_DIR}/src/config.h nofs.hpp io.h blockl.hpp logl.hpp)

configure_file (config.h.in ${PROJECT_BINARY_DIR}/src/config.h)

include_directories (. ${PROJECT_BINARY_DIR}/src)

add_link_options (-lpthread)
add_compile_options (-Werror -Wall -Wextra)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED True)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED True)

add_library (nofs SHARED ${SRC_LIST})
add_library (nofs_s STATIC ${SRC_LIST})
set_target_properties (nofs_s PROPERTIES OUTPUT_NAME "nofs")
set_target_properties (nofs PROPERTIES VERSION ${NOFS_VERSION} SOVERSION ${NOFS_VERSION})

install (TARGETS nofs nofs_s LIBRARY DESTINATION lib ARCHIVE DESTINATION)

install (FILES ${HEADER_LIST} DESTINATION include/nofs)


