#!/bin/bash

#Build for Linux
cd ..
rm -rf build
mkdir build
cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
make -j16
