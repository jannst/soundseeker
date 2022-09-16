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

#define sine_pwm_uint uint8_t
#define pwm_buf_size 2048

void print_lut(uint16_t pwm_num_samples);
uint8_t sine_pwm_lut[pwm_buf_size];

bool generate_sine_pwm(double amplitude, uint16_t pwm_num_samples);
bool play_frequency(double amplitude, double frequency);
int init_pwm();

#endif