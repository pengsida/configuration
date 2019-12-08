#!/bin/bash

sudo apt install autoconf

wget https://github.com/google/protobuf/archive/v3.3.0.zip
unzip protobuf

cd protobuf-3.3.0/
./autogen.sh
./configure
make

sudo make isntall
sudo ldconfig
