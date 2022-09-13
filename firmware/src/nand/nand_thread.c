# include "main.h"
#include "sync_functions.h"

#define D4 18
#define D5 19
#define D6 20
#define D7 21

#define RS 16
#define E 17


void init_pin(uint val) {
    gpio_init(val);
    gpio_set_dir(val, GPIO_OUT);
}

void pulseE() {
    gpio_put(E, 1);
    sleep_us(100);
    gpio_put(E, 0);
    sleep_us(100);
}

void send2LCD4(uint8_t val) {
    gpio_put(D4, (val & 0b00000001) >>0);
    gpio_put(D5, (val & 0b00000010) >>1);
    gpio_put(D6, (val & 0b00000100) >>2);
    gpio_put(D7, (val & 0b00001000) >>3);
    pulseE();
}

void send2LCD8(uint8_t val) {
    send2LCD4(val >> 4);
    send2LCD4(val);
}

void lcd_setup() {
    gpio_put(RS, 0);
    send2LCD4(0b0011);
    send2LCD4(0b0011);
    send2LCD4(0b0011);
    send2LCD4(0b0010);
    send2LCD8(0b00101000);
    send2LCD8(0b00001100);
    send2LCD8(0b00000110);
    send2LCD8(0b00000001);
    sleep_ms(150);
}

void lcd_clear() {
    gpio_put(RS, 0);
    sleep_us(100);
    send2LCD8(0x01);
    send2LCD8(0x02);
    sleep_ms(150);
    gpio_put(RS, 1);
}

static const char* test = "Hallo :)";

void nand_thread_init() {
    printf("ok1");
    init_pin(D4);
    init_pin(D5);
    init_pin(D6);
    init_pin(D7);
    init_pin(RS);
    init_pin(E);
    lcd_setup();

    gpio_put(RS, 1);

}

static uint32_t blink_interval_ms = 64;
void nand_thread(void) {
    queue_entry_t entry;
    while(1) {
        queue_peek_blocking(&job_queue, &entry);
        lcd_clear();
        for(uint32_t i = 0; i < entry.len-1; i++) {
            send2LCD8(entry.buf[i]);
        }
        printf_sync("dat: %.*s", entry.len, entry.buf);
        sleep_ms(100);
        queue_remove_blocking(&job_queue, &entry);
    }
}

