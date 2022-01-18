#!/bin/bash

# step 1: install a nvidia driver of proper version
# version 384 fits the Titan Xp
sudo add-apt-repository ppa:graphics-drivers/ppa
sudo apt-get update
sudo apt-get install nvidia-384
sudo reboot

sudo nvidia-xconfig --allow-empty-initial-configuration
sudo reboot

# step 2: install the cuda-9.0
# NOTE: don't install the nvidia driver inside the cuda-9.0
sudo ./cuda_9.0.176_384.81_linux-run --no-opengl-lib

# step 3: install the cudnn
tar xf cudnn-9.0-linux-x64-v7.tgz
cd cuda/include
sudo cp *.h /usr/local/cuda/include/
cd ..
cd lib64/
sudo cp lib* /usr/local/cuda/lib64/
cd /usr/local/cuda/lib64
sudo rm -rf libcudnn.so libcudnn.so.7
sudo ln -s libcudnn.so.7.0.5 libcudnn.so.7
sudo ln -s libcudnn.so.7 libcudnn.so

# step 4: set up the environment variable
echo "export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64" | sudo tee -a /etc/bash.bashrc

