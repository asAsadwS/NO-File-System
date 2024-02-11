#ifndef NO_FILE_SYSTEM_SPINLOCK_H
#define NO_FILE_SYSTEM_SPINLOCK_H

#include <stdint.h>

struct T_SPINLOCK {
	void* lock_ptr;
};

int spinlock_get ( struct T_SPINLOCK& lock );
int spinlock_tryget ( struct T_SPINLOCK& lock );

int spinlock_release ( struct T_SPINLOCK& lock );

int spinlock_create ( struct T_SPINLOCK& lock );
int spinlock_delete ( struct T_SPINLOCK& lock );

#endif
