#ifndef SOUNDSEEKER_DEFINES
#define SOUNDSEEKER_DEFINES

// power supply for piezo driver
#define ENABLE_PIEZO_DRIVER_PIN 8

// power supply for piezo sensor amplifier
#define ENABLE_ANALOG_POWER_SUPPLY_PIN 9

// TODO add R2R ladder pins


// --- ADC SPI ---
#define ADC_SPI spi0
#define ADC_SPI_RX_PIN 16
#define ADC_SPI_CSN_PIN 17
#define ADC_SPI_SCK_PIN 18
#define ADC_SPI_TX_PIN 19

#endif