#include "./blockl.hpp"
#include "./io.hpp"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

T_BLOCK::T_BLOCK (size_t block_size){
	void* alloc_mem = malloc (block_size);
	if (alloc_mem == NULL) ppanic(-1, "Error while trying allocing memory.");
	memset (alloc_mem, 0, block_size);
	this -> data = alloc_mem;
};
T_BLOCK::~T_BLOCK (){
	free (this -> data);
};

uint8_t T_BLOCK::read (size_t offset, void* buffer, size_t buffer_size){
	size_t real_start = offset + buffer_size;
	if (real_start > this -> block_size)
		return -1;
	else
		real_start = offset;


	if (memcpy (buffer, (void*)((size_t)(this -> data) + real_start), buffer_size) != NULL) {
		return -1;
	};

	return 0;
};

uint8_t T_BLOCK::write (size_t offset, void* buffer, size_t buffer_size){
	size_t real_start = offset + buffer_size;
	if (real_start > this -> block_size)
		return -1;
	else
		real_start = offset;

	if (memcpy ((void*)((size_t)(this -> data) + real_start), buffer, buffer_size) != NULL) {
		return -1;
	};

	return 0;
};


uint8_t T_BLOCKGROUP::read (size_t offset, void* buffer){
	if (offset+this -> each_size > this -> total_size)
		return -1;
	memcpy (buffer, (void*)((size_t)(this -> data)+offset), this -> each_size);
	return 0;
};
uint8_t T_BLOCKGROUP::write (size_t offset, void* buffer){
	if (offset+this -> each_size > this -> total_size)
		return -1;
	memcpy ((void*)((size_t)(this -> data)+offset), buffer, this -> each_size);
	return 0;
};
uint8_t T_BLOCKGROUP::zero (size_t offset){
	if (offset+this -> each_size > this -> total_size)
		return -1;
	memset ((void*)((size_t)(this -> data)+offset), 0, this -> each_size);
	return 0;
}; // Fill a block with 0.

T_BLOCKGROUP::T_BLOCKGROUP (size_t block_size, size_t block_count){
	this -> data = malloc (block_size * block_count);
	if (this -> data == NULL) ppanic(-1, "Can not alloc memory.");

	this -> is_alloc = true;
	this -> each_size = block_size;
	this -> total_size = block_size * block_count;
	return;
};
T_BLOCKGROUP::T_BLOCKGROUP (void* disk, size_t disk_size, size_t block_size){
	if (disk == NULL)
		ppanic(-1, "The point can not be NULL.");

	this -> data = disk;
	this -> each_size = block_size;
	this -> total_size = disk_size;
	this -> is_alloc = false;
	return;
};

T_BLOCKGROUP::~T_BLOCKGROUP (){};
