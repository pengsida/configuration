#!/bin/bash

wget "http://cdn2.ime.sogou.com/dl/index/1524572264/sogoupinyin_2.2.0.0108_amd64.deb"
sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb
sudo apt-get install -f
sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb

