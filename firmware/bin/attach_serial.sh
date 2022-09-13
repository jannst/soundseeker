#!/bin/bash
# example:
# ./attach_serial.sh /dev/ttyACM1

#Leave minicom: CTRL+A, then press X
minicom -b 115200 -o -D "$1"