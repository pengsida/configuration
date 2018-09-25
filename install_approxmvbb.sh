#!/bin/bash

git clone https://github.com/gabyx/ApproxMVBB.git ApproxMVBB
cd ApproxMVBB
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="/usr/local/" ..
make all -j8
sudo make install

