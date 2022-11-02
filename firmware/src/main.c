#include "signal_generator/signal_generator.h"
#include "soundseeker.h"

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

  //signal_freq_ocillator_demo();

  uint freq = 40000;
  bool change = true;

  while(true) {
    //sine_play_pulses(0.2, freq, 2);
    //if(change) {
    sine_play_pulses(.1, freq, 3);
    time_us_64();
      //change = false;
    //}
    sleep_us(10000);
    /*
    int c = 0;//getchar();
    if(c) {
      if(c == 119) {
        freq += 20;
      }
      if(c == 115) {
        freq -= 20;
      }
      change = true;
      printf("new freq: %d\n", freq);
    }
    */
  }

  //signal_amplitude_ocillator_demo();

  while (1)
    tight_loop_contents();
}
