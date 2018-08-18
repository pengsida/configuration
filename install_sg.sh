#!/bin/bash

sudo add-apt-repository ppa:eugenesan/ppa
sudo apt-get update
sudo apt-get install smartgit
sudo apt-get install openjdk-8-jdk
sudo ln -s /usr/share/smartgit/bin/smartgit.sh /usr/local/bin/smartgit.sh

