#include "main.h"

#define PWM_PIN 0

int main(void) {
    stdio_init_all();
    //usb_thread_init();
    //nand_thread_init();
    //init_sync_functions();

    //queue_init(&job_queue, sizeof(queue_entry_t), 1);
    //printf("Initialisation finished! Launching threads!\n");
    //sleep_ms(100);
    //multicore_launch_core1(nand_thread);
    //usb_thread();



    setup_pwm();
    printf("Pwm init done :)\n");
    while (1)
        tight_loop_contents();
}
