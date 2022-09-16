#include "main.h"

#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "r2r_ladder.pio.h"

#define num_bits 6
#define pin_offset 2
#define num_samples 2000

void display(uint8_t val)
{
  for (uint8_t i = 0; i < num_bits; i++)
  {
    // printf("(%d) write pin %d: %d | ", val, pin_offset+i, 1u & (val >> (num_bits-i-1)));
    gpio_put(pin_offset + i, 1u & (val >> (num_bits - i - 1)));
  }

}

static PIO pio;
static uint sm;
void pio_init()
{
  // Choose which PIO instance to use (there are two instances)
  pio = pio0;

  // Our assembled program needs to be loaded into this PIO's instruction
  // memory. This SDK function will find a location (offset) in the
  // instruction memory where there is enough space for our program. We need
  // to remember this location!
  uint offset = pio_add_program(pio, &r2r_ladder_program);

  // Find a free state machine on our chosen PIO (erroring if there are
  // none). Configure it to run our program, and start it, using the
  // helper function we included in our .pio file.
  sm = 0; // pio_claim_unused_sm(pio, true);

  r2r_ladder_program_init(pio, sm, offset, pin_offset, num_bits);

  // make the tx FIFO steal the bits from rx FIFO and become twice as big
  //pio->sm[sm].shiftctrl = pio->sm[sm].shiftctrl | PIO_SM0_SHIFTCTRL_FJOIN_TX_BITS;
  // pio->sm[sm].shiftctrl = pio->sm[sm].shiftctrl | PIO_SM0_SHIFTCTRL_PULL_THRESH_BITS;
}

int dma_channel;

void dma_handler()
{
  // Clear the interrupt request.
  dma_hw->ints0 = 1u << dma_channel;
  // Set DMA read address back to base addres of lookup table, and re-trigger
  // sleep_us(5);
  dma_channel_set_read_addr(dma_channel, sine_pwm_lut, true);
}

void dma_init()
{
  dma_channel = dma_claim_unused_channel(true);

  dma_channel_config dma_config = dma_channel_get_default_config(dma_channel);
  channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_32);
  channel_config_set_dreq(&dma_config, pio_get_dreq(pio, sm, true));

  uint16_t num_dwords = (num_samples + (5 - 1)) / 5;
  dma_channel_configure(dma_channel,
                        &dma_config,
                        &pio->txf[sm],
                        NULL, // set by dma_handler
                        num_dwords,
                        false);

  irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
  dma_channel_set_irq0_enabled(dma_channel, true);
  irq_set_enabled(DMA_IRQ_0, true);
}




int main(void)
{
  //set_sys_clock_khz(126000, true);
  stdio_init_all();
  generate_sine_pwm(.8, num_samples);
  puts("now check lut");
  print_lut(num_samples);

  uint8_t value = 0;
  pio_init();
  dma_init();

  pio_sm_put_blocking(pio, sm, num_samples);
  dma_handler();

  while (true)
  {
    //sleep_ms(1000);
    //dma_channel_set_irq0_enabled(dma_channel, false);
    //sleep_ms(1000);
    //dma_channel_set_irq0_enabled(dma_channel, true);
    //dma_handler();
  }

  uint f_clk_sys = frequency_count_mhz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
  printf("clk_sys  = %dMHz\n", f_clk_sys);
  printf("Pwm init done :)\n");
  while (1)
    tight_loop_contents();
}
