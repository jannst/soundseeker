#include "main.h"


#include "hardware/dma.h"
#include "hardware/clocks.h"

int main(void) {
    set_sys_clock_khz(126000, true);
    stdio_init_all();
    //usb_thread_init();
    //nand_thread_init();
    //init_sync_functions();

    //queue_init(&job_queue, sizeof(queue_entry_t), 1);
    //printf("Initialisation finished! Launching threads!\n");
    //sleep_ms(100);
    //multicore_launch_core1(nand_thread);
    //usb_thread();


    generate_sine_pwm(.5);
    setup_pwm();
    uint f_clk_sys = frequency_count_mhz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    printf("clk_sys  = %dMHz\n", f_clk_sys);
    printf("Pwm init done :)\n");
    while (1)
        tight_loop_contents();
}
