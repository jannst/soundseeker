cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(firmware_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


file(GLOB_RECURSE SOURCE_FILES src/*.c)
add_executable(firmware_pico ${SOURCE_FILES} src/driver/port.h src/driver/raw/test.c)

#add_executable(firmware_pico
#        src/main.c
#        src/usb_descriptors.c
#        src/usb/usb_thread.c
#        src/nand/nand_thread.c
#        src/usb/usb_status_blink.c
#        src/usb/usb_device_handler.c
#        src/sync_functions.c
#        src/driver/raw/nand_amd.c
#        )

pico_generate_pio_header(firmware_pico ${CMAKE_CURRENT_LIST_DIR}/src/parallel_nand.pio)


# Make sure TinyUSB can find tusb_config.h
target_include_directories(firmware_pico PRIVATE src)


#pico_enable_stdio_usb(firmware_pico 1)
pico_enable_stdio_uart(firmware_pico 1)
pico_add_extra_outputs(firmware_pico)
target_link_libraries(firmware_pico PRIVATE pico_stdlib tinyusb_device tinyusb_board hardware_pio hardware_sync pico_multicore)

