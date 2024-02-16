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
#include "config.hpp"

#include <cstring>
#include <utility>

namespace nofs {

T_LOGPNODE::T_LOGPNODE (void* buffer, size_t buffer_size) {
	void* copyed_buffer = NULL;
	copyed_buffer = malloc(buffer_size);
	if (copyed_buffer == nullptr){
		ppanic (-1, "Unable to alloc the memory.");
	};

	memcpy (copyed_buffer, buffer, buffer_size);
	this -> buffer = copyed_buffer;
	this -> size = buffer_size;

	fprintf(stderr, "Create a T_LOGPNODE\n");

	return;
};

T_LOGPNODE::T_LOGPNODE(T_LOGPNODE&& move){
	*this = std::move(move);
	fprintf(stderr, "Move con a T_LOGPNODE\n");
};

T_LOGPNODE& T_LOGPNODE::operator=(T_LOGPNODE&& move){
	if (this != &move){
		this -> buffer = move.buffer;
		this -> size = move.size;
		move.buffer = nullptr;
		move.size = 0;
	};
	fprintf(stderr, "Move a T_LOGPNODE\n");
	return *this;
};

T_LOGPNODE::~T_LOGPNODE (){
	if (this -> buffer != nullptr){
		free (this -> buffer);
	};
	fprintf(stderr, "Delete a T_LOGPNODE\n");
	return;
};

T_LOGPOOL::T_LOGPOOL (const char* path){
	fprintf(stderr, "Create a T_LOGPOOL\n");

	auto disk = new T_DISK(path);
	this -> disk = disk;
	this -> cache = std::unordered_map<size_t,T_LOGPNODE>(LOG_CACHE_SIZE);
	return;
};

uint8_t T_LOGPOOL::write (size_t offset, void* buffer, size_t size){
	this -> lock.lock();

//	this -> cache.emplace(std::make_pair(offset, T_LOGPNODE(buffer, size)));
	this -> cache.insert ({offset, T_LOGPNODE (buffer, size)});

	this -> lock.unlock();
	return 0;
};

uint8_t T_LOGPOOL::flush (){
	this -> lock.lock();

	for (auto item = this -> cache.begin();item != this -> cache.end();item++){
		this -> disk -> write (item -> first, item -> second.buffer, item -> second.size);
	};
	this -> cache.clear();

	this -> lock.unlock();
	return 0;
};


T_LOGPOOL::~T_LOGPOOL (){
	fprintf(stderr, "Delete a T_LOGPOOL\n");
	delete this -> disk;
};

};
