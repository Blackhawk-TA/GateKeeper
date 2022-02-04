# Gate Keeper

[![license](https://img.shields.io/github/license/Blackhawk-TA/GateKeeper)](https://github.com/Blackhawk-TA/GateKeeper/blob/master/LICENSE.md)
![Build](https://github.com/Blackhawk-TA/GateKeeper/workflows/Build/badge.svg)
[![github](https://img.shields.io/github/release/Blackhawk-TA/GateKeeper.svg?color=brightgreen)](https://github.com/Blackhawk-TA/GateKeeper/releases)

An RPG game called GateKeeper made for the 32blit and PicoSystem retro consoles. \
It also runs on Linux, MacOS and Windows.

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
make GateKeeper
```

PicoSystem:
```
mkdir build.pico
cd build.pico
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico.toolchain -DPICO_BOARD=pimoroni_picosystem
make
```

## Sprites
All sprites were created by [Gif](https://gif-superretroworld.itch.io/), [Noiracide](https://noiracide.itch.io/) and [TheRoro](https://drpixelo.itch.io/).
The packs can be found here: https://gif-superretroworld.itch.io.
The non character enemies were made by [vryell](https://vryell.itch.io/tiny-enemies-vol1).
The weapon sprites were made by [franuka](https://franuka.itch.io/). \
I modified all character sprites to fit the 16x16 tile bounds.
The white tiles with borders used for in game menus were made by me.
