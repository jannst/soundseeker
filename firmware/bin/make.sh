#!/bin/bash

#Used to generate the binaries using make

basedir="$(dirname $0)/.."

set -e

cd "${basedir}/build"

make -j8

cd --