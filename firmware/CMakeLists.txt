cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(firmware_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


# put this in to add all *.c file to compilation
file(GLOB_RECURSE SOURCE_FILES src/*.c)
add_executable(firmware_pico ${SOURCE_FILES})

#add_executable(firmware_pico
#        src/main.c
#        )

#pico_generate_pio_header(firmware_pico ${CMAKE_CURRENT_LIST_DIR}/src/parallel_nand.pio)


# Make sure TinyUSB can find tusb_config.h
#target_include_directories(firmware_pico PRIVATE src)


#pico_enable_stdio_usb(firmware_pico 1)
pico_enable_stdio_uart(firmware_pico 1)
pico_add_extra_outputs(firmware_pico)
target_link_libraries(firmware_pico PRIVATE 
    pico_stdlib 
    hardware_pwm
    hardware_dma
    )

# used like this in nand programmer
#target_link_libraries(firmware_pico PRIVATE pico_stdlib tinyusb_device tinyusb_board hardware_pio hardware_sync pico_multicore)

