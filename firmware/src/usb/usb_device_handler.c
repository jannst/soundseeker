#include "usb_device_handler.h"
#include "sync_functions.h"
#include "main.h"

void usb_loopback_task() {
    static uint32_t num_bytes;
    if(tud_vendor_mounted()) {
        if(tud_vendor_write_available() >=64) {
            //tud_vendor_write(data_tx_buf, 64);
            //printf_sync("tud_vendor_write_available!\n");
            //puts("wrote string");
        }
        static uint32_t bytesAvail;
        if ((bytesAvail = tud_vendor_available()) && queue_is_empty(&job_queue)) {
            num_bytes = tu_min32(bytesAvail,sizeof(data_rx_buf));
            tud_vendor_read(data_rx_buf, num_bytes);
            queue_entry_t entry = {(uint8_t *) data_rx_buf, num_bytes};
            queue_try_add(&job_queue, &entry);
        }
    }


}
