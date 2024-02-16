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

#include "logl.hpp"
#include "io.hpp"
#include "config.hpp"

struct T_SPBLOCK {
	uint32_t magic_num = MAGIC_NUM;
	uint16_t version;
	uint8_t lock;
	uint8_t file_limit;
	uint8_t __PRESERVE1;
	uint8_t block_size;
	uint64_t block_count;
	uint64_t block_used;
	uint64_t inode_count;
	uint64_t inode_used;
	uint64_t inode_entry;
	uint64_t bitmap_entry;
	uint8_t __PRESERVE2[0];
};

struct T_INODE {
	uint64_t ctime; // create time
	uint64_t mtime; // edit time
	uint64_t rtime; // access time
	uint16_t attr;
	uint16_t owner;
	uint32_t __PRESERVE1;
	uint64_t __PRESERVE2[2];
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

T_LOGPOOL::T_LOGPOOL (const char* path) {
	this -> disk_file = std::fopen (path, "r+");
	if (this -> disk_file == NULL) {
		ppanic (-1, "The file is not avaibile.");
	};

	struct T_SPBLOCK super_block;
	if (fread (&super_block, sizeof (super_block), 1, this -> disk_file) != sizeof(super_block)){
		ppanic (-1, "The file is not avaibile.");
	};

	if (super_block.magic_num != MAGIC_NUM){
		ppanic (-1, "Invaild file.");
	};

	this -> cache = std::list<void*> (512);
};
T_LOGPOOL::~T_LOGPOOL () {};

