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

#include "io.hpp"
#include "config.hpp"
#include "macro.hpp"
#include <cstring>

namespace nofs {

static inline uint8_t write_file(FILE* file, void* buffer, size_t size){
	if (fwrite (buffer, 1, size, file) != size){
		ppanic (-1, "Unable to write.");
	};
	return 0;
};

T_DISK::T_DISK (const char* file_path){
	this -> file = fopen (file_path, "r+");

	if (file == nullptr) {
		ppanic (-1, "Can not open the file.");
	};

	uint32_t disk_magic_num;
	fread (&disk_magic_num, 1, sizeof(disk_magic_num), file);
	if (disk_magic_num ^ MAGIC_NUM) {
		ppanic (-1, "This file is not a vaild NOFS file.");
	};

	uint16_t block_size = 0;
	fread (&block_size, 1, sizeof(block_size), file);
	this -> block_size = 1 << block_size;
};

T_DISK::T_DISK (FILE* file){
	if (file == nullptr) {
		ppanic (-1, "Can not open the file.");
	};

	uint32_t disk_magic_num;
	fread (&disk_magic_num, 1, sizeof(disk_magic_num), file);
	if (disk_magic_num ^ MAGIC_NUM) {
		ppanic (-1, "This file is not a vaild NOFS file.");
	};

	uint16_t block_size = 0;
	fread (&block_size, 1, sizeof(block_size), file);
	this -> block_size = 1 << block_size;
};

uint8_t T_DISK::create (const char* path, uint32_t block_size, size_t block_count){
	uint16_t bits = 0;
	size_t p_block_size = block_size;
	if (block_size == 0){
		ppanic (-1, "Block size can not be zero.");
	};
	do {
		bits++;
		if (block_size % 2 != 0){
			ppanic (-1, "Invaild block size.");
		};
		block_size /= 2;
	} while (block_size != 1);
	

	FILE* dest_file = fopen (path, "w+");
	if (dest_file == NULL){
		ppanic (-1, "Unable to create the file");
	};

	uint32_t magic_num = MAGIC_NUM;

	write_file (dest_file, &magic_num, sizeof(magic_num));

	if (p_block_size < sizeof(magic_num)){
		ppanic(-1, "Invaild block size.");
	};

	uint8_t use_write[p_block_size];
	memset (use_write, 0, p_block_size);

	write_file (dest_file, &bits, sizeof(bits));

	write_file (dest_file, use_write, p_block_size - sizeof(bits) - sizeof(magic_num));

	block_count--;

	while (block_count != 0){
		write_file (dest_file, use_write, p_block_size);
		block_count--;
	};

	fclose (dest_file);

	return 0;
};

uint8_t T_DISK::bread (size_t offset, void* buffer){
	this -> lock.lock();
	
	fseek (this -> file, offset * this -> block_size, SEEK_SET);
	fread (buffer, 1, this -> block_size, this -> file);

	this -> lock.unlock();
	return 0;
};

uint8_t T_DISK::bwrite (size_t offset, void* buffer){
	this -> lock.lock();
	
	fseek (this -> file, offset * this -> block_size, SEEK_SET);
	if (fwrite (buffer, 1, this -> block_size, this -> file) != this -> block_size){
		ppanic (-1, "Can't flush this block.");
	};

	this -> lock.unlock();
	return 0;
};

uint8_t T_DISK::write (size_t offset, void* buffer, size_t size) {
	this -> lock.lock();

	fseek (this -> file, offset, SEEK_SET);
	if (fwrite (buffer, 1, size, this -> file) != size){
		ppanic (-1, "Can't flush this block.");
	};

	this -> lock.unlock();
	return 0;
};

uint8_t T_DISK::read (size_t offset, void* buffer, size_t size) {
	this -> lock.lock();

	fseek (this -> file, offset, SEEK_SET);
	fread (buffer, 1, size,this -> file);

	this -> lock.unlock();
	return 0;
};


T_DISK::~T_DISK (){
	fclose (this -> file);
	this -> block_size = 0;
	return;
};

};
