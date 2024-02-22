/*
	Copyright (C) 2024  asAsadwS

	NO-File-System is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	NO-File-System  is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with NO-File-System.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef NO_FILE_SYSTEM_MACRO_HPP
#define NO_FILE_SYSTEM_MACRO_HPP

#include <cstdint>

#define ppanic(ret_code, message) \
	do { \
		fprintf(stderr, "[NOFS]:%s:%d:%s: %s\n",__FILE__,__LINE__,__func__,message);\
		fflush(stderr);\
		exit(ret_code);\
	} while (0)

#endif
