# 32Blit RPG game

[![license](http://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Blackhawk-TA/32blit-rpg/blob/master/LICENSE.md)
![Build](https://github.com/Blackhawk-TA/32blit-rpg/workflows/Build/badge.svg)
[![github](https://img.shields.io/github/release/Blackhawk-TA/32blit-rpg.svg?color=brightgreen)](https://github.com/Blackhawk-TA/TowerDefense/releases)

A yet unnamed RPG game for the 32blit retro console.

## Build
Linux:
```
mkdir build
cd build
cmake ..
make
```

32Blit:
```
mkdir build.stm32
cd build.stm32
cmake .. -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make 32blit-rpg
```
