###############################################################
# File Name: build.sh
# Author: Yongda Zhu
# mail: yongda.zhu@email.ucr.edu
# Created Time: Thu Sep 26 16:37:48 2019
###############################################################
#!/bin/bash

clang++ -Xclang -fopenmp -o go main.cc -lomp
