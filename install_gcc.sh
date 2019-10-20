#!/bin/bash

wget https://ftp.gnu.org/gnu/gcc/gcc-5.4.0/gcc-5.4.0.tar.gz
tar xvzf gcc-5.4.0.tar.gz
cd gcc-5.4.0
./contrib/download_prerequisites
./configure --with-system-zlib --disable-multilib --enable-languages=c,c++
sudo make -j8
sudo make install

