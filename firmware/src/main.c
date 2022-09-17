#include "signal_generator/signal_generator.h"

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

  signal_freq_ocillator_demo();
  //signal_amplitude_ocillator_demo();

  while (1)
    tight_loop_contents();
}
