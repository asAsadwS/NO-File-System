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

#include <cstdint>

namespace nofs {
	uint32_t MAGIC_NUM = (('N' << 24) + ('O' << 16) + ('F' << 8) + 'S');
	uint32_t LOG_CACHE_SIZE = 1024;
	uint32_t BLOCK_GROUP_EACH_COUNT = 1024;
};
