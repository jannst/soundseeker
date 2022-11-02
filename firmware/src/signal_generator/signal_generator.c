#include "signal_generator.h"

/**
 * Generate the sine wave pwm lookup table
 * \param amplitude range from 0.0 to 1.0
 *
 * Have a look at this appnote for more info: (page 13)
 * https://www.renesas.com/kr/en/document/apn/pwm-sine-wave-generation-sinewave?language=en
 **/
void generate_sine_lookup_table(double amplitude)
{
    for (uint16_t i = 0; i < SINE_NUM_SAMPLES; i++)
    {
        sine_lookup_table[i] = (uint8_t)(sin(2 * i * M_PI / SINE_NUM_SAMPLES) * amplitude * (USED_DAC_RESOLUTION / 2) + (DAC_RESOLUTION / 2) - 1);
    }
}


void sine_dma_handler()
{
    // Clear the interrupt request.
    dma_hw->ints0 = 1u << dma_channel;

    if(playback_pulse_mode) {
        if(num_remaining_pulses > 0) {
            num_remaining_pulses--;
        } else {
            return;
        }
    }

    // Set DMA read address back to base addres of lookup table, and re-trigger
    dma_channel_set_read_addr(dma_channel, sine_lookup_table, true);
}


void sine_generator_init()
{
    // Setup PIO
    signal_pio = pio0;
    r2r_program_offset = pio_add_program(signal_pio, &r2r_ladder_program);
    signal_sm = pio_claim_unused_sm(signal_pio, true);


    // Setup DMA
    dma_channel = dma_claim_unused_channel(true);
    dma_channel_config dma_config = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_8);
    channel_config_set_dreq(&dma_config, pio_get_dreq(signal_pio, signal_sm, true));

    dma_channel_configure(dma_channel,
                          &dma_config,
                          &signal_pio->txf[signal_sm],
                          NULL, // set by dma_handler
                          SINE_NUM_SAMPLES,
                          false);

    irq_set_exclusive_handler(DMA_IRQ_0, sine_dma_handler);
    dma_channel_set_irq0_enabled(dma_channel, true);
    irq_set_enabled(DMA_IRQ_0, true);

    //r2r_ladder_program_init(signal_pio, signal_sm, r2r_program_offset, SIGNAL_OUT_PIN_BASE, DAC_NUM_BITS, SINE_NUM_SAMPLES, 40000);
    //pio_sm_put_blocking(signal_pio, signal_sm, 0xFFFFFFFF);
}


void sine_playback_reset()
{
    dma_channel_set_irq0_enabled(dma_channel, false);
    dma_channel_abort(dma_channel);
    num_remaining_pulses = 0;
    playback_pulse_mode = false;
}


void sine_playback_init(float amplitude, uint frequency) {
    generate_sine_lookup_table(amplitude);
    r2r_ladder_program_init(signal_pio, signal_sm, r2r_program_offset, SIGNAL_OUT_PIN_BASE, DAC_NUM_BITS, SINE_NUM_SAMPLES, frequency);
    dma_channel_set_irq0_enabled(dma_channel, true);
}


bool sine_play(float amplitude, uint frequency)
{
    sine_playback_reset();
    sine_playback_init(amplitude, frequency);
    // run the dma handler manually to start transmission
    sine_dma_handler();
}


bool sine_play_pulses(float amplitude, uint frequency, uint number_of_pulses)
{
    sine_playback_reset();
    sine_playback_init(amplitude, frequency);
    playback_pulse_mode = true;
    num_remaining_pulses = number_of_pulses;
    // run the dma handler manually to start transmission
    sine_dma_handler();
}