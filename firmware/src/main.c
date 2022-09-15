#include "main.h"


#include "hardware/dma.h"
#include "hardware/clocks.h"

#define num_bits 6
#define pin_offset 2

void display(uint8_t val) {
  for(uint8_t i = 0; i < num_bits; i++) {
    //printf("(%d) write pin %d: %d | ", val, pin_offset+i, 1u & (val >> (num_bits-i-1)));
    gpio_put(pin_offset+i, 1u & (val >> (num_bits-i-1)));
  }
}

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


    //init_pwm();

    //play_frequency(0.5, 40000);
    //sleep_ms(2000);
    //play_frequency(0.5, 40000);

    uint8_t value = 0;

    for(uint8_t i = 0; i < num_bits; i++) {
      gpio_init(pin_offset+i);
      gpio_set_dir(pin_offset+i, GPIO_OUT);
    }




    // Initialize chosen serial port
    stdio_init_all();

    // Loop forever
    while (true) {  
        display(value);
        value++;
        if(value >= 64) {
          value = 0;
        }
        //sleep_us(1);
        //puts("");
    }


    uint f_clk_sys = frequency_count_mhz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    printf("clk_sys  = %dMHz\n", f_clk_sys);
    printf("Pwm init done :)\n");
    while (1)
        tight_loop_contents();
}
