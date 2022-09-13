#include "main.h"
#include "sync_functions.h"

int main(void) {
    stdio_init_all();
    usb_thread_init();
    nand_thread_init();
    init_sync_functions();

    queue_init(&job_queue, sizeof(queue_entry_t), 1);
    printf("Initialisation finished! Launching threads!\n");
    sleep_ms(100);
    multicore_launch_core1(nand_thread);
    usb_thread();
    /*
    pio_init();


      // The state machine is now running. Any value we push to its TX FIFO will
      // appear on the LED pin.
      while (1) {
          // Blink
          pio_sm_put_blocking(pio, sm, 1);
          sleep_ms(50);
          // Blonk
          pio_sm_put_blocking(pio, sm, 0);
          sleep_ms(500);
      }




    while (1) {
        tud_task(); // tinyusb device task
        led_blinking_task();

        usb_loopback_task();
        //hid_task();
    }

      */

    return 0;
}



/*
static PIO pio;
static uint sm;

void pio_init() {
      // Choose which PIO instance to use (there are two instances)
    pio = pio0;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    uint offset = pio_add_program(pio, &parallel_nand_program);

    // Find a free state machine on our chosen PIO (erroring if there are
    // none). Configure it to run our program, and start it, using the
    // helper function we included in our .pio file.
    sm = pio_claim_unused_sm(pio, true);
    parallel_nand_program_init(pio, sm, offset, PICO_DEFAULT_LED_PIN);
}
*/
