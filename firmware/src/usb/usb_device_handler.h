#ifndef FIRMWARE_PICO_USB_DEVICE_HANDLER_H
#define FIRMWARE_PICO_USB_DEVICE_HANDLER_H

#include "bsp/board.h"

static uint8_t *cmd_rx_buf[64];
static uint8_t *cmd_tx_buf[64];

static uint8_t *data_rx_buf[2048];
static uint8_t *data_tx_buf[2048];

void usb_loopback_task();

#endif //FIRMWARE_PICO_USB_DEVICE_HANDLER_H
