#ifndef NO_FILE_SYSTEM_IO_HPP
#define NO_FILE_SYSTEM_IO_HPP

#include <stdio.h>

#define ppanic(ret_code, message) \
	do { \
		fprintf(stderr, "[NOFS]:%s:%d:%s:%s\n",__FILE__,__LINE__,__func__,message);\
		fflush(stderr);\
		exit(ret_code);\
	} while (0)

#endif
