#ifndef FIRMWARE_PICO_SIGNAL
#define FIRMWARE_PICO_SIGNAL

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "r2r_ladder.pio.h"

#define DAC_NUM_BITS 6
#define SIGNAL_OUT_PIN_BASE 2
#define DAC_RESOLUTION (1u << DAC_NUM_BITS)   // DAC can display values from 0 to 63
#define USED_DAC_RESOLUTION 62                // the signal generator will only use 62 values
#define SINE_NUM_SAMPLES 128

bool playback_pulse_mode;
uint num_remaining_pulses;
uint8_t sine_lookup_table[SINE_NUM_SAMPLES];

// PIO
static PIO signal_pio;
static uint signal_sm;
uint r2r_program_offset;

// DMA
int dma_channel;

// Functions
void sine_generator_init();
void sine_playback_reset();
bool sine_play(float amplitude, uint frequency);
bool sine_play_pulses(float amplitude, uint frequency, uint number_of_pulses);

#endif