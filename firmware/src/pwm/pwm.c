#include "pwm.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

/**
 * Check out this appnote on creating pwm audio:
 * http://ww1.microchip.com/downloads/en/Appnotes/90003250A.pdf
 **/

/**
 * Generate the sine wave pwm lookup table
 *
 * Have a look at this appnote: (page 13)
 *  https://www.renesas.com/kr/en/document/apn/pwm-sine-wave-generation-sinewave?language=en
 * \param amplitude range from 0.0 to 1.0
 **/

// actually 64 but only 62 to have 2 buffer
#define pwm_resolution 64
#define effective_pwm_resolution 62
uint16_t pwm_num_samples;
bool generate_sine_pwm(double amplitude, uint16_t pwm_num_samples)
{
    if (pwm_num_samples >= pwm_buf_size)
    {
        printf("ERROR: Could not generate pwm lookup table. number of samples %d bigger than buffer %d", pwm_num_samples, pwm_buf_size);
        return false;
    }

    for (uint16_t i = 0; i < pwm_num_samples; i++)
    {
        sine_pwm_lut[i] = (sine_pwm_uint)(sin(2 * i * M_PI / pwm_num_samples) * amplitude * (effective_pwm_resolution / 2) + (pwm_resolution / 2) - 1);
        printf("%d: %d\n", i, sine_pwm_lut[i]);
    }
    return true;
}

int dma_channel;

void dma_handlerx()
{
    // Clear the interrupt request.
    dma_hw->ints0 = 1u << dma_channel;
    // Set DMA read address back to base addres of lookup table, and re-trigger
    // sleep_us(5);
    dma_channel_set_read_addr(dma_channel, sine_pwm_lut, true);
}

int init_pwm()
{
    gpio_set_function(PWM_OUT, GPIO_FUNC_PWM);

    uint pwm_slice_num = pwm_gpio_to_slice_num(PWM_OUT);
    uint pwm_channel = pwm_gpio_to_channel(PWM_OUT);

    pwm_config pwm_config = pwm_get_default_config();
    // tell pwm counter to count up to 'pwm_resolution'
    pwm_config_set_wrap(&pwm_config, pwm_resolution);
    pwm_init(pwm_slice_num, &pwm_config, true);
    // pwm_set_chan_level(pwm_slice_num, pwm_channel, pwm_resolution/2);
}

void configure_dma()
{
    if (!dma_channel)
    {
        dma_channel = dma_claim_unused_channel(true);
    }

    uint pwm_slice_num = pwm_gpio_to_slice_num(PWM_OUT);
    uint pwm_channel = pwm_gpio_to_channel(PWM_OUT);

    dma_channel_config dma_config = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_16);
    channel_config_set_dreq(&dma_config, pwm_get_dreq(pwm_slice_num));

    // Super important to specifiy the correct PWM channel for the selected GPIO pin.
    // Check https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#io-user-bank-function-table for reference
    // E.g: GPIO 2 is selected for PWM output.
    // Then Base Addr for DMA is PWM_BASE + PWM_CH1_CC_OFFSET
    // if channel is B, increment the write address by 2 bytes because pwm values have 16 bits
    volatile void *pwm_level_register = pwm_channel ? &pwm_hw->slice[pwm_slice_num].cc + 2 : &pwm_hw->slice[pwm_slice_num].cc;

    dma_channel_configure(
        dma_channel,
        &dma_config,
        pwm_level_register,
        sine_pwm_lut,
        pwm_num_samples, // Number of transfers
        false            // Do not start immediately.
    );

    dma_channel_set_irq0_enabled(dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handlerx);
    irq_set_enabled(DMA_IRQ_0, true);
}

bool play_frequency(double amplitude, double frequency)
{
    if (dma_channel && dma_channel_is_busy(dma_channel))
    {
        // dma_channel_set_irq0_enabled(dma_channel, false);
        // sleep_ms(1);
        // dma_channel_abort(dma_channel);

        // init_pwm();
        dma_channel_set_irq0_enabled(dma_channel, true);
        irq_set_exclusive_handler(DMA_IRQ_0, dma_handlerx);
        irq_set_enabled(DMA_IRQ_0, true);
        sleep_ms(1);
        // irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
        // irq_set_enabled(DMA_IRQ_0, true);
        // dma_hw->ints0 = 1u << dma_channel;
        dma_channel_start(dma_channel);
        dma_handlerx();
    }
    else
    {

        if (!generate_sine_pwm(amplitude, frequency))
        {
            return false;
        }
        configure_dma();
        dma_handlerx();
    }
    return true;
}