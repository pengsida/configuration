#!/bin/bash

sudo apt-get install meld
cd ~
wget https://github.com/pengsida/configuration/raw/master/git-diffall
sudo mv git-diffall /usr/local/bin/git-diffall
sudo chmod 777 /usr/local/bin/git-diffall
git config --global merge.tool meld
git config –global alias.diffall git-diffall

