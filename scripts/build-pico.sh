#!/bin/bash

#Build for PicoSystem
cd ..
rm -rf build.pico
mkdir build.pico
cd build.pico || exit
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico.toolchain -DPICO_BOARD=pimoroni_picosystem
make -j16
