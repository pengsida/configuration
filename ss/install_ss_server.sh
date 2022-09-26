#!/bin/bash

export LC_ALL=en_US.UTF-8
sudo apt-get install -y python-pip
sudo apt-get install -y git
sudo pip install setuptools
sudo pip install git+https://github.com/shadowsocks/shadowsocks.git@master
