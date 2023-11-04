#!/bin/bash

#Build for 32Blit
cd ..
rm -rf build.stm32
mkdir build.stm32
cd build.stm32 || exit 1
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make -j16 GateKeeper

source ../.venv/bin/activate
sudo 32blit install GateKeeper.blit
