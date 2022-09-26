#!/bin/bash

sudo apt-get install wget tar libevent-dev libncurses-dev
export VERSION=2.6
mkdir ~/tmux-src
wget -qO- https://github.com/tmux/tmux/releases/download/${VERSION}/tmux-${VERSION}.tar.gz | tar xvz -C ~/tmux-src
cd ~/tmux-src/tmux*
./configure
make -j8
sudo make install
