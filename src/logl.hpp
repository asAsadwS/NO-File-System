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

#ifndef NO_FILE_SYSTEM_LOGL_HPP
#define NO_FILE_SYSTEM_LOGL_HPP

#include <cstdio>
#include <mutex>
#include <list>

class T_LOGPOOL {
private:
	std::mutex lock;
	std::list<void*> cache;
	std::FILE* disk_file;
public:
	T_LOGPOOL (const char* path);
	~T_LOGPOOL ();

	uint8_t write (size_t offset, void* buffer, size_t size);

	uint8_t flush (void);
	uint8_t check (void);
	uint8_t sync (void);
};

#endif
