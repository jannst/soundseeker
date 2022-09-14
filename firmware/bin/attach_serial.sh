#!/bin/bash
# example:
# ./attach_serial.sh /dev/ttyACM1

# make sure to have to have udev rules setup on your system.
# Check "raspberry picoprobe udev rules" on google

#Leave minicom: CTRL+A, then press X
minicom -b 115200 -o -D "$1"
