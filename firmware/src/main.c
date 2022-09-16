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

int main(void)
{
  stdio_init_all();
  sine_generator_init();

  signal_amplitude_ocillator_demo();

  while (1)
    tight_loop_contents();
}
