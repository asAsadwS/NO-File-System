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

#ifndef NO_FILE_SYSTEM_BLOCKL_HPP
#define NO_FILE_SYSTEM_BLOCKL_HPP

#include <stdint.h>

class T_BLOCK {
private:
	size_t block_size;
	void* data;

public:
	uint8_t read (size_t offset, void* buffer, size_t buffer_size);
	uint8_t write (size_t offset, void* buffer, size_t buffer_size);

	T_BLOCK (size_t alloc_block_size);
	~T_BLOCK ();
};

/*
 *	'T_BLOCKGROUP' operate data as some blocks whose size is 'each_size'.
 *	Please make sure the buffer have enough space to store a bloxk.
 */

class T_BLOCKGROUP {
private:
	bool is_alloc;
	size_t each_size;
	size_t total_size;
	void* data;
public:
	uint8_t read (size_t offset, void* buffer);
	uint8_t write (size_t offset, void* buffer);
	uint8_t zero (size_t offset); // Fill a block with 0.

	T_BLOCKGROUP (size_t block_size, size_t block_count);
	T_BLOCKGROUP (void* disk, size_t disk_size, size_t block_size);

	~T_BLOCKGROUP ();
};


#endif

