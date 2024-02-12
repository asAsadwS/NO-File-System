#ifndef NO_FILE_SYSTEM_SPINLOCK_H
#define NO_FILE_SYSTEM_SPINLOCK_H

#include <stdint.h>

volatile struct T_SPINLOCK {
};

uint8_t spinlock_get ( struct T_SPINLOCK& lock );
uint8_t spinlock_tryget ( struct T_SPINLOCK& lock );

uint8_t spinlock_release ( struct T_SPINLOCK& lock );

uint8_t spinlock_create ( struct T_SPINLOCK& lock );
uint8_t spinlock_delete ( struct T_SPINLOCK& lock );

#endif
