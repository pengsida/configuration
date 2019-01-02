#!/bin/bash

sudo apt-get install -y python-pip
sudo apt-get install -y git
sudo pip install setuptools
sudo pip install git+https://github.com/shadowsocks/shadowsocks.git@master

nohup /usr/bin/python /usr/local/bin/sslocal -s x.x.x.x -p 9050 -k xxxx -m aes-256-cfb &

sudo apt-get install -y privoxy
sudo mv /etc/privoxy/config /etc/privoxy/config.bak
sudo touch /etc/privoxy/config
echo 'forward-socks5 / localhost:1080 .' | sudo tee -a  /etc/privoxy/config
echo 'listen-address localhost:8118' | sudo tee -a  /etc/privoxy/config
sudo service privoxy restart
sudo touch /usr/local/bin/proxy
echo '#!/bin/bash' | sudo tee -a  /usr/local/bin/proxy
echo 'export http_proxy=http://localhost:8118' | sudo tee -a  /usr/local/bin/proxy
echo 'export https_proxy=http://localhost:8118' | sudo tee -a  /usr/local/bin/proxy
echo '$*' | sudo tee -a  /usr/local/bin/proxy
sudo chmod 777 /usr/local/bin/proxy
# or consider to use meow

