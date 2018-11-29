#!/bin/bash

mkdir -p ~/Software/ss
cd ~/Software/ss
wget https://github.com/wwtalwtaw/configuration/raw/master/doc/ss/server_linux_amd64
chmod 777 server_linux_amd64
nohup ssserver -p 8388 -k xxxx -m aes-256-cfb > /dev/null &
nohup ./server_linux_amd64 -l :29900 -t 127.0.0.1:8388 -key xxxx -mtu 1400 -sndwnd 2048 -rcvwnd 2048 -mode fast2 > /dev/null

