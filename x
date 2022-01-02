#!/bin/bash
TYPE=abc
TIME=203
# -D_GLIBCXX_DEBUG をつかうと, lower_bound が使えなかったので
g++ -g -D_DEBUG -std=c++17 -Wall -O2 ./atcoder/$TYPE/$TIME/$1.cpp
echo compiled
./a.out
