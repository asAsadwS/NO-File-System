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

#include "nofs.hpp"
#include "macro.hpp"
#include "struct.hpp"
#include <malloc.h>
#include <cstring>

#define CALC_INODE_NUM(block_size, block_count) ((block_size / sizeof(T_INODE))*BLOCK_GROUP_EACH_COUNT)

namespace nofs {

uint8_t create (const char* path, uint32_t block_size, size_t block_count){
	T_DISK::create (path, block_size, block_count);
	T_DISK* disk = new T_DISK(path);
	uint8_t* block_write;
	block_write = (uint8_t*)malloc (block_size);

	if (block_write == nullptr){
		ppanic (-1, "Unable to alloc memory.");
	};

	disk -> bread (0,block_write);

	{
		T_SPBLOCK tmp_block;
		tmp_block.block_count = block_count;
		tmp_block.block_size = block_write[5];
		tmp_block.magic_num  = MAGIC_NUM;
		tmp_block.inode_count = CALC_INODE_NUM (block_size, block_count);
		disk -> write (0, &tmp_block, sizeof(tmp_block));
	};
	
	free (block_write);

	return 0;
};

T_NOFS::T_NOFS (const char* path){
	this -> logpool = new T_LOGPOOL(path);
	this -> disk = &(this -> logpool -> indisk());

	return;
};
/*
T_FILE&& T_NOFS::find (const char* path){
};
*/

T_NOFS::~T_NOFS (){

};

};


