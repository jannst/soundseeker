#include <pico/printf.h>
#include "sync_functions.h"
#include "pico/lock_core.h"

lock_core_t printf_lock;

void init_sync_functions() {
    lock_init(&printf_lock, (uint) spin_lock_claim_unused(true));
}


int printf_sync(const char *format, ...) {
    va_list args;
    uint32_t safe = spin_lock_blocking(printf_lock.spin_lock);
    va_start(args, format);
        int retval= vprintf(format, args);
    va_end(args);
    spin_unlock(printf_lock.spin_lock, safe);
    return retval;
}


