#!/bin/bash

#Used to flash the firmware_pico.elf onto the pico using openocd.
#The used prorammer is another Raspberry Pi Pico configured as a picoprobe

set -e

executable="$(dirname $0)/../build/firmware_pico.elf"

openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program ${executable} verify reset exit"
