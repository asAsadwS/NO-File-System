#     Copyright (C) 2024  asAsadwS

#     NO-File-System is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.

#     NO-File-System  is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.

#     You should have received a copy of the GNU General Public License
#     along with NO-File-System.  If not, see <https://www.gnu.org/licenses/>.


cmake_minimum_required (VERSION 3.15)

set (NOFS_VERSION_MAJOR 0)
set (NOFS_VERSION_MINOR 1)
set (NOFS_VERSION_PATCH 0)
set (NOFS_VERSION ${NOFS_VERSION_MAJOR}.${NOFS_VERSION_MINOR}.${NOFS_VERSION_PATCH})

project (NOFS LANGUAGES C CXX VERSION ${NOFS_VERSION})

add_subdirectory (src)

#include (CMakePackageConfigHelpers)

#write_basic_package_version_file (
#	${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#	VERSION ${NOFS_VERSION}
#	COMPATIBILITY SameMinorVersion
#	)

#configure_package_config_file (
#	${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
#	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#	NO_SET_AND_CHECK_MACRO
#	PATH_VARS CMAKE_INSTALL_PREFIX
#	INSTALL_DESTINATION lib/cmake
#	)

#install (FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake DESTINATION lib/cmake/${PROJECT_NAME})
