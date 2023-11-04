#!/bin/bash

#Build for PicoSystem
cd ..
rm -rf build.pico
mkdir build.pico
cd build.pico || exit 1
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico.toolchain -DPICO_BOARD=pimoroni_picosystem
make -j16
