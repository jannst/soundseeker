#ifndef FIRMWARE_PICO_PWM
#define FIRMWARE_PICO_PWM

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define PWM_OUT 2

void on_pwm_wrap();
int setup_pwm();

#endif