#include "pwm.h"

/**
 * Generate the sine wave pwm lookup table
 * 
 * Have a look at this appnote: (page 13)
 *  https://www.renesas.com/kr/en/document/apn/pwm-sine-wave-generation-sinewave?language=en
 * \param amplitude range from 0.0 to 1.0
 **/
#define pwm_resolution 41
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
    
/*
    pwm_set_chan_level(pwm_slice_num, PWM_CHAN_A, 0);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, (sine_pwm_uint)-1);
    pwm_config_set_clkdiv(&config, 1);
    pwm_init(pwm_slice_num, &config, true);
    
    */

    // Tell the LED pin that the PWM is in charge of its value.
    gpio_set_function(PWM_OUT, GPIO_FUNC_PWM);
    // Figure out which slice we just connected to the LED pin
    uint pwm_slice_num = pwm_gpio_to_slice_num(PWM_OUT);
    uint pwm_channel = pwm_gpio_to_channel(PWM_OUT);


    //pwm_set_chan_level(pwm_slice_num, PWM_CHAN_A, 0);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, pwm_resolution);


    pwm_init(pwm_slice_num, &config, true);

    //pwm_set_wrap(pwm_slice_num, (sine_pwm_uint)-1);
    //pwm_set_chan_level(pwm_slice_num, PWM_CHAN_A, 0);
    //pwm_set_enabled(pwm_slice_num, true);


    // Get a free channel, panic() if there are none
    if (!dma_channel)
    {
        dma_channel = dma_claim_unused_channel(true);
    }



/*
static inline void pwm_set_chan_level(uint slice_num, uint chan, uint16_t level) {
    check_slice_num_param(slice_num);
    hw_write_masked(
        &pwm_hw->slice[slice_num].cc,
        ((uint)level) << (chan ? PWM_CH0_CC_B_LSB : PWM_CH0_CC_A_LSB),
        chan ? PWM_CH0_CC_B_BITS : PWM_CH0_CC_A_BITS
    );
}
*/




    // 8 bit transfers. Both read and write address increment after each
    // transfer (each pointing to a location in src or dst respectively).
    // No DREQ is selected, so the DMA transfers as fast as it can.
    if(!dma_channel_is_busy(dma_channel)) {
        dma_channel_config config = dma_channel_get_default_config(dma_channel);
        channel_config_set_transfer_data_size(&config, DMA_SIZE_16);
        channel_config_set_dreq(&config, pwm_get_dreq(pwm_slice_num));

        // Super important to specifiy the correct PWM channel for the selected GPIO pin.
        // Check https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#io-user-bank-function-table for reference 
        // E.g: GPIO 2 is selected for PWM output.
        // Then Base Addr for DMA is PWM_BASE + PWM_CH1_CC_OFFSET
        // if channel is B, increment the write address by 2 bytes because pwm values have 16 bits
        volatile void* pwm_level_register = pwm_channel ? &pwm_hw->slice[pwm_slice_num].cc + 2 : &pwm_hw->slice[pwm_slice_num].cc;

        dma_channel_configure(
            dma_channel,
            &config,
            //pwm_level_register,
            (void*)(PWM_BASE + PWM_CH1_CC_OFFSET),
            sine_pwm_lut,
            count_of(sine_pwm_lut),     // Number of transfers
            false                       // Do not start immediately.
        );

        dma_channel_set_irq0_enabled(dma_channel, true);
        irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
        irq_set_enabled(DMA_IRQ_0, true);
        dma_handler();
    }
    
}