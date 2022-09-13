#include "usb_status_blink.h"
#include "bsp/board.h"
#include "usb_device_handler.h"

void usb_thread_init() {
    board_init();
    tusb_init();
}

_Noreturn int usb_thread(void) {
    while (1) {
        tud_task(); // tinyusb device task
        usb_stat_led_blink_task();
        usb_loopback_task();
    }
}

