#!/bin/bash

#Build for Linux
cd ..
rm -rf build
mkdir build
cd build
cmake ..
make
