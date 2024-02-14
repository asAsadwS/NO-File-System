#   Copyright (C) 2024  asAsadwS

#   NO-File-System is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   NO-File-System  is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with NO-File-System.  If not, see <https://www.gnu.org/licenses/>.

set (NOFS_VERSION_MAJOR 0)
set (NOFS_VERSION_MINOR 0)
set (NOFS_VERSION_PATCH 0)
set (NOFS_VERSION ${NOFS_VERSION_MAJOR}.${NOFS_VERSION_MINOR}.${NOFS_VERSION_PATCH})

set (TIMESTAMP G_COMPILE_TIME %y%m%d)

set (SRC_LIST nofs.cpp blockl.cpp logl.cpp config.cpp)
set (HEADER_LIST ${PROJECT_BINARY_DIR}/src/add.h nofs.hpp io.hpp blockl.hpp logl.hpp config.hpp)

configure_file (add.h.in ${PROJECT_BINARY_DIR}/src/add.h)

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


