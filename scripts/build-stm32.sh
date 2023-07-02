#!/bin/bash

#Build for 32Blit
cd ..
rm -rf build.stm32
mkdir build.stm32
cd build.stm32
cmake .. -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make -j16 GateKeeper
