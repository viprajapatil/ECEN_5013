#! /bin/bash

#change directory
cd /home/vipraja/kernel/linux-4.14.13

make menuconfig
make -j2 > kernel-build.log
sudo make modules_install >> kernel-build.log
sudo make install >> kernel-build.log
