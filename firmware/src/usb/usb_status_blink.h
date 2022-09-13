#ifndef FIRMWARE_PICO_USB_STATUS_BLINK_H
#define FIRMWARE_PICO_USB_STATUS_BLINK_H

#include <stdint.h>
#include <stdbool.h>

#include "bsp/board.h"

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 2500,
};
static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;
void usb_stat_led_blink_task(void);

#endif //FIRMWARE_PICO_USB_STATUS_BLINK_H
