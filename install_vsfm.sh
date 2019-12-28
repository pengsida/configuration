# Install Nvidia CUDA if you have an CUDA capable Nvidia GPU (optional)
# CUDA documentation -> https://docs.nvidia.com/cuda/
# Check compatibility -> https://developer.nvidia.com/cuda-gpus
# Download the CUDA toolkit  -> http://developer.nvidia.com/cuda/cuda-downloads

sudo dpkg -i cuda-repo-ubuntu1604_9.1.85-1_amd64.deb
sudo apt-key adv --fetch-keys http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1604/x86_64/7fa2af80.pub
sudo apt update
sudo apt install cuda nvidia-cuda-dev nvidia-cuda-toolkit

# Maybe add this to your ~/.bashrc
export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib:$LD_LIBRARY_PATH


# Install dependencies
sudo apt install \
    libgtk2.0-dev \
    libglew-dev \
    libdevil-dev \
    libboost-all-dev \
    libatlas-cpp-0.6-dev \
    libatlas-dev \
    imagemagick \
    libatlas3-base \
    libcminpack-dev \
    libgfortran3 \
    libmetis-edf-dev \
    libparmetis-dev \
    freeglut3-dev \
    libgsl-dev \
    glew-utils


# Download and extract VisualSFM
# http://ccwu.me/vsfm/index.html

wget http://ccwu.me/vsfm/download/VisualSFM_linux_64bit.zip
unzip VisualSFM_linux_64bit.zip
rm VisualSFM_linux_64bit.zip


# Download and install SiftGPU in the appropriate directory
# https://github.com/pitzer/SiftGPU

cd ~/vsfm
wget https://github.com/pitzer/SiftGPU/archive/master.zip
unzip master.zip
rm master.zip
mv SiftGPU-master SiftGPU

cd ~/vsfm/SiftGPU
make
cp ~/vsfm/SiftGPU/bin/libsiftgpu.so ~/vsfm/bin

# Download and install Multicore Bundle Adjustment ('pba') in the appropriate directory
# http://grail.cs.washington.edu/projects/mcba/

cd ~/vsfm
wget http://grail.cs.washington.edu/projects/mcba/pba_v1.0.5.zip
unzip pba_v1.0.5.zip
rm pba_v1.0.5.zip

cd ~/vsfm/pba
# Try using the following commands if the make command failed
# echo -e "#include <stdlib.h>\n$(cat ~/vsfm/pba/src/pba/SparseBundleCU.h)" > ~/vsfm/pba/src/pba/SparseBundleCU.h
# echo -e "#include <stdlib.h>\n$(cat ~/vsfm/pba/src/pba/pba.h)" > ~/vsfm/pba/src/pba/pba.h
make
cp ~/vsfm/pba/bin/libpba.so ~/vsfm/vsfm/bin/

# Download, hack and install PMVS in the appropriate directory
# http://www.di.ens.fr/pmvs/documentation.html

cd ~/vsfm
wget http://www.di.ens.fr/pmvs/pmvs-2.tar.gz
tar xvzf pmvs-2.tar.gz
rm pmvs-2.tar.gz

cd ~/vsfm/pmvs-2/program/main/
cp ~/vsfm/pmvs-2/program/main/mylapack.o ~/vsfm/pmvs-2/program/main/mylapack.o.backup
make clean
cp ~/vsfm/pmvs-2/program/main/mylapack.o.backup ~/vsfm/pmvs-2/program/main/mylapack.o
make depend
make


# Download and install Graclus1.2
# http://www.cs.utexas.edu/users/dml/Software/graclus.html

cd ~/vsfm
wget http://www.cs.utexas.edu/users/dml/Software/graclus1.2.tar.gz
tar xvzf graclus1.2.tar.gz
rm graclus1.2.tar.gz
sed -i 's/COPTIONS = -DNUMBITS=32/COPTIONS = -DNUMBITS=64/' ~/vsfm/graclus1.2/Makefile.in
make


# Download, hack and install CMVS in the appropriate directory
# http://www.di.ens.fr/cmvs/documentation.html

cd ~/vsfm
wget http://www.di.ens.fr/cmvs/cmvs-fix2.tar.gz
tar xvzf cmvs-fix2.tar.gz
rm cmvs-fix2.tar.gz

cp ~/vsfm/pmvs-2/program/main/mylapack.o ~/vsfm/cmvs/program/main/

echo -e "#include <vector>\n#include <numeric>\n$(cat ~/vsfm/cmvs/program/base/cmvs/bundle.cc)" > ~/vsfm/cmvs/program/base/cmvs/bundle.cc
echo -e "#include <stdlib.h>\n$(cat ~/vsfm/cmvs/program/main/genOption.cc)" > ~/vsfm/cmvs/program/main/genOption.cc
sed -e '/Your INCLUDE path*/ s/^#*/#/' -i ~/vsfm/cmvs/program/main/Makefile
sed -e '/Your metis directory*/ s/^#*/#/' -i ~/vsfm/cmvs/program/main/Makefile
sed -e '/Your LDLIBRARY path*/ s/^#*/#/' -i ~/vsfm/cmvs/program/main/Makefile

sed -i "s:YOUR_INCLUDE_METIS_PATH =*:YOUR_INCLUDE_METIS_PATH = -I$HOME/vsfm/graclus1.2/metisLib:" ~/vsfm/cmvs/program/main/Makefile
sed -i "s:YOUR_LDLIB_PATH =*:YOUR_LDLIB_PATH = -L$HOME/vsfm/graclus1.2:" ~/vsfm/cmvs/program/main/Makefile


cd ~/vsfm/cmvs/program/main
make
cp ~/vsfm/cmvs/program/main/cmvs ~/vsfm/bin
cp ~/vsfm/cmvs/program/main/pmvs2 ~/vsfm/bin
cp ~/vsfm/cmvs/program/main/genOption ~/vsfm/bin


cd ~/vsfm
make

# Maybe add this to your ~/.bashrc
export PATH=$PATH:$HOME/vsfm/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/vsfm/bin