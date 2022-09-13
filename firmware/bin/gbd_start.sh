#!/bin/bash

#Open gdb server

set -e

#executable="$(dirname $0)/../build/firmware_pico.elf"
executable="$(dirname $0)/../cmake-build-debug/firmware_pico.elf"
openocd -f interface/picoprobe.cfg -f target/rp2040.cfg