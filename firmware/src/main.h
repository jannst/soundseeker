#ifndef FIRMWARE_PICO_MAIN_H
#define FIRMWARE_PICO_MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <pico/util/queue.h>

#include "bsp/board.h"
#include "pico/stdlib.h"
#include "pico/mutex.h"
#include "pico/multicore.h"

_Noreturn
int usb_thread();
void usb_thread_init();
_Noreturn
void nand_thread();
void nand_thread_init();

typedef struct
{
    uint8_t *buf;
    uint32_t len;
} queue_entry_t;
queue_t job_queue;

#endif //FIRMWARE_PICO_MAIN_H
