#include "signal_generator/signal_generator.h"
#include "soundseeker.h"
#include "hardware/spi.h"
#include <string.h>

void signal_amplitude_ocillator_demo()
{
  bool up = true;
  float amplitude = 0;
  while (true)
  {
    sleep_ms(100);
    sine_play(amplitude, 40000);

    if (up)
    {
      if (amplitude >= 1)
      {
        amplitude = 1;
        up = false;
      }
      else
      {
        amplitude += 0.05;
      }
    }
    else
    {
      if (amplitude <= 0)
      {
        amplitude = 0;
        up = true;
      }
      else
      {
        amplitude -= 0.05;
      }
    }
  }
}

void signal_freq_ocillator_demo()
{
  bool up = true;
  float freq = 30000;
  while (true)
  {
    sleep_ms(50);
    sine_play(.2, freq);

    if (up)
    {
      if (freq >= 50000)
      {
        freq = 50000;
        up = false;
      }
      else
      {
        freq += 1000;
      }
    }
    else
    {
      if (freq <= 1000)
      {
        freq = 1000;
        up = true;
      }
      else
      {
        freq -= 1000;
      }
    }
  }
}

#define ADC_BUF_LEN 3000
uint16_t adc_buf[ADC_BUF_LEN];
uint dma_rx;
uint dma_tx;
uint timer;
dma_channel_config c;
uint16_t write_val = 0;
void sample_adc()
{
    if (dma_channel_is_busy(dma_rx) || dma_channel_is_busy(dma_tx)) {
        return;
    }

    dma_channel_config c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
    channel_config_set_dreq(&c, dma_get_timer_dreq(timer));
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, false);
    dma_channel_configure(dma_tx, &c,
                          &spi_get_hw(spi_default)->dr, // write address
                          &write_val, // read address
                          ADC_BUF_LEN, // element count (each element is of size transfer_data_size)
                          false); // don't start yet

  c = dma_channel_get_default_config(dma_rx);
  channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
  channel_config_set_dreq(&c, spi_get_dreq(ADC_SPI, false));
  // do not increment pointer pointing to SPI data register
  channel_config_set_read_increment(&c, false);
  // but update the pointer pointing to the buffer
  channel_config_set_write_increment(&c, true);
  dma_channel_configure(dma_rx, &c,
                        adc_buf,                  // write address
                        &spi_get_hw(ADC_SPI)->dr, // read address
                        ADC_BUF_LEN,              // element count (each element is of size transfer_data_size)
                        false);                   // don't start yet

  // start ADC sampling
  dma_start_channel_mask((1u << dma_rx) | (1u << dma_tx));
}

int main(void)
{
  stdio_init_all();
  sine_generator_init();

  gpio_init(ENABLE_PIEZO_DRIVER_PIN);
  gpio_init(ENABLE_ANALOG_POWER_SUPPLY_PIN);

  gpio_set_dir(ENABLE_PIEZO_DRIVER_PIN, GPIO_OUT);
  gpio_set_dir(ENABLE_ANALOG_POWER_SUPPLY_PIN, GPIO_OUT);

  gpio_put(ENABLE_PIEZO_DRIVER_PIN, 0);
  gpio_put(ENABLE_ANALOG_POWER_SUPPLY_PIN, 1);

  // signal_freq_ocillator_demo();

  uint freq = 40000;
  bool change = true;


  const char* EOL = "ENDE";
  const char* START = "DATA";

  // Enable SPI 0 at 1 MHz and connect to GPIOs
  spi_init(ADC_SPI, 32 * 1000 * 1000);
  spi_set_format(spi_default, 16, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);

  gpio_set_function(ADC_SPI_RX_PIN, GPIO_FUNC_SPI);
  gpio_set_function(ADC_SPI_SCK_PIN, GPIO_FUNC_SPI);
  gpio_set_function(ADC_SPI_CSN_PIN, GPIO_FUNC_SPI);
  // gpio_set_function(ADC_SPI_TX_PIN, GPIO_FUNC_SPI);

  // setup SPI DMA
  dma_rx = dma_claim_unused_channel(true);
  dma_tx = dma_claim_unused_channel(true);


  uint timer = dma_claim_unused_timer(true);
  dma_timer_set_fraction(timer, 1, 125);
  // We set the inbound DMA to transfer from the SPI receive FIFO to a memory buffer paced by the SPI RX FIFO DREQ
  // We configure the read address to remain unchanged for each element, but the write
  // address to increment (so data is written throughout the buffer)

  
    //sine_play_pulses(1, freq, 3);
    //sine_play_pulses(1, freq, 3);
    //sine_play(1, freq);
  while(true) {
    sine_play_pulses(.1, freq, 30);
    sample_adc();
    sleep_ms(500);
    uint16_t *wordPtr = adc_buf;
    uint8_t *bytePtr = (uint8_t *)adc_buf;
    for (uint i = 0; i < ADC_BUF_LEN; i++)
    {
      // shift 7 bits because of ADC data format (see data sheet for MAX1115 ADC)
      if((*wordPtr >> 7) < 10) {
        printf("oh oh :(\n");
      }
      *bytePtr = (uint8_t)(*wordPtr >> 7);
      bytePtr++;
      wordPtr++;
    }
    //printf(START);
    //uart_write_blocking (uart0, (uint8_t*)&adc_buf[0], ADC_BUF_LEN);
    //printf(EOL);
  }

  while (1)
    tight_loop_contents();
}
