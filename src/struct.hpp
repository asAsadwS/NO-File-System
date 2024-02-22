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

#ifndef NO_FILE_SYSTEM_STRUCT_HPP
#define NO_FILE_SYSTEM_STRUCT_HPP

#include "config.hpp"
#include <cstdint>

namespace nofs {

struct T_SPBLOCK {
	uint32_t magic_num = MAGIC_NUM;
	uint8_t block_size;
	struct {
		uint16_t major;
		uint16_t minor;
		uint16_t patch;
	} version;
	uint8_t lock;
	uint64_t block_count;
	uint64_t block_used;
	uint64_t inode_count;
	uint64_t inode_used;
	uint64_t inode_entry;
	uint64_t bitmap_entry;
	uint8_t __PRESERVE2[0];
};

struct T_INODE {
	uint64_t htime; // change time
	uint64_t ctime; // create time
	uint64_t mtime; // edit time
	uint64_t rtime; // access time
	uint16_t attr;
	uint16_t owner;
	uint32_t __PRESERVE1;
	uint64_t __PRESERVE2[1];
	uint64_t size;
	uint64_t file_count;
	struct {
		uint64_t direct[6];
		uint64_t rdirect[3];
		uint64_t drdirect[2];
		uint64_t trdirect[1];
	} data;
	struct {
		uint64_t direct[6];
		uint64_t rdirect[3];
		uint64_t drdirect[2];
		uint64_t trdirect[1];
	} dir;
};

};

#endif
