#! /bin/bash

echo "User name                   : $(id -un)" > info.txt
echo "Host name                   : $(uname -n)" >> info.txt  
echo "Operating system            : $(uname -o)" >> info.txt
echo "OS Distribution             : $(lsb_release -i)" >> info.txt
echo "Kernel version              : $(uname -r)" >> info.txt
echo "Kernel gcc version build    : $(cat /proc/version)" >> info.txt
echo "Kernel build time           : $(uname -v)" >> info.txt
echo "System architecture info    : $(uname -m)" >> info.txt
echo "File system memory          :              
$(free -m)" >> info.txt                          






