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

#ifndef NO_FILE_SYSTEM_NOFS_H
#define NO_FILE_SYSTEM_NOFS_H

#include "logl.hpp"

namespace nofs {

class T_FILE;

class T_NOFS {
private:
	T_LOGPOOL* logpool;
	T_DISK* disk;
public:
	static uint8_t create (const char* path, uint32_t block_size, size_t block_count);
	T_NOFS (const char* path);

	T_FILE&& find (const char* path);

	uint8_t read (T_FILE& file);
	uint8_t write (T_FILE& file);
	uint8_t flush (T_FILE& file);

	~T_NOFS ();
};

class T_FILE {
friend T_NOFS;
private:
	T_NOFS* ref_fs;
	size_t node_num;
	size_t _padding;
	struct {
		size_t size;
		uint64_t ctime;
		uint64_t mtime;
		uint64_t htime;
		uint64_t rtime;
	} file;
public:
	T_FILE ();
	T_FILE (T_FILE&& move);
	~T_FILE();

	T_FILE& operator = (T_FILE&& move);

	uint8_t read (size_t offset, void* buffer, size_t size);
	uint8_t write (size_t offset, void* buffer, size_t size);
	const char* path (void);
	size_t size (void);
};

}; 

#endif
