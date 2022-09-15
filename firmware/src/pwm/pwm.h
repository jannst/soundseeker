#ifndef FIRMWARE_PICO_PWM
#define FIRMWARE_PICO_PWM

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"

#define PWM_OUT 2

#define sine_pwm_uint uint16_t
#define pwm_num_samples 40

sine_pwm_uint sine_pwm_lut[pwm_num_samples];

void generate_sine_pwm(double amplitude);
void on_pwm_wrap();
int setup_pwm();

#endif