#!/bin/bash

mkdir -p ~/Software/ss
cd ~/Software/ss
wget https://github.com/wwtalwtaw/configuration/raw/master/doc/ss/client_linux_amd64
chmod 777 client_linux_amd64
nohup ./client_linux_amd64 -r "127.0.0.1:3333" -l ":9050" -key xxxx -mtu 1400 -sndwnd 256 -rcvwnd 2048 -mode fast2 -dscp 46 > /dev/null &
nohup sslocal -s 127.0.0.1 -p 9050 -k xxxx -m aes-256-cfb > /dev/null &

