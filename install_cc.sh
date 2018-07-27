#!/bin/bash

git clone --recursive https://github.com/cloudcompare/trunk.git
sudo apt-get install -y build-essential
sudo apt-get install -y qt5-default
sudo apt-get install -y libqt5svg5-dev
sudo apt-get install -y cmake

cd trunk
mkdir build
cd build
cmake ..
make -j 8
sudo make install

