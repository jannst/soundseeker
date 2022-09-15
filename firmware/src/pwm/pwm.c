#include "pwm.h"

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
#define pwm_resolution 62
void generate_sine_pwm(double amplitude)
{
    for (uint16_t i = 0; i < pwm_num_samples; i++)
    {
        sine_pwm_lut[i] = (sine_pwm_uint)(sin(2 * i * M_PI / pwm_num_samples) * amplitude * (pwm_resolution / 2) + (pwm_resolution / 2)-1);
        printf("%d: %d\n", i, sine_pwm_lut[i]);
    }
}

int dma_channel;


void dma_handler() {
    // Clear the interrupt request.
    dma_hw->ints0 = 1u << dma_channel;
    // Set DMA read address back to base addres of lookup table, and re-trigger
    dma_channel_set_read_addr(dma_channel, sine_pwm_lut, true);
}

int setup_pwm()
{
    gpio_set_function(PWM_OUT, GPIO_FUNC_PWM);

    uint pwm_slice_num = pwm_gpio_to_slice_num(PWM_OUT);
    uint pwm_channel = pwm_gpio_to_channel(PWM_OUT);

    pwm_config pwm_config = pwm_get_default_config();
    // tell pwm counter to count up to 'pwm_resolution'
    pwm_config_set_wrap(&pwm_config, pwm_resolution);
    pwm_init(pwm_slice_num, &pwm_config, true);


    dma_channel = dma_claim_unused_channel(true);
    dma_channel_config dma_config = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_16);
    channel_config_set_dreq(&dma_config, pwm_get_dreq(pwm_slice_num));

    // Super important to specifiy the correct PWM channel for the selected GPIO pin.
    // Check https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#io-user-bank-function-table for reference 
    // E.g: GPIO 2 is selected for PWM output.
    // Then Base Addr for DMA is PWM_BASE + PWM_CH1_CC_OFFSET
    // if channel is B, increment the write address by 2 bytes because pwm values have 16 bits
    volatile void* pwm_level_register = pwm_channel ? &pwm_hw->slice[pwm_slice_num].cc + 2 : &pwm_hw->slice[pwm_slice_num].cc;

    dma_channel_configure(
        dma_channel,
        &dma_config,
        pwm_level_register,
        //(void*)(PWM_BASE + PWM_CH1_CC_OFFSET),
        sine_pwm_lut,
        count_of(sine_pwm_lut),     // Number of transfers
        false                       // Do not start immediately.
    );

    dma_channel_set_irq0_enabled(dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
    dma_handler();
    
}