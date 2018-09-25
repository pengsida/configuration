# Setup introduction

Use the following script to compile the program:

```bash
export LD_PRELOAD=''
mkdir build
cd build
cmake ..
make
export LD_PRELOAD=/usr/lib/gcc/x86_64-linux-gnu/5/libasan.so
```

