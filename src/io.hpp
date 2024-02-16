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

#ifndef NO_FILE_SYSTEM_IO_HPP
#define NO_FILE_SYSTEM_IO_HPP

#include <cstdio>
#include <cstdint>
#include <mutex>

#define ppanic(ret_code, message) \
	do { \
		fprintf(stderr, "[NOFS]:%s:%d:%s: %s\n",__FILE__,__LINE__,__func__,message);\
		fflush(stderr);\
		exit(ret_code);\
	} while (0)

namespace nofs {

class T_DISK {
private:
	FILE* file;
	std::mutex lock;
	size_t block_size;
public:
	static uint8_t create (const char* path, uint32_t block_size, size_t block_count);

	uint8_t bread (size_t offset, void* buffer);
	uint8_t bwrite (size_t offset, void* buffer);
	
	uint8_t read (size_t offset, void* buffer, size_t size);
	uint8_t write (size_t offset, void* buffer, size_t size);

	T_DISK (const char* file_path);
	T_DISK (FILE* file);
	~T_DISK ();

	size_t get_block_size();
};

};

#endif
