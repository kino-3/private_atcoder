#!/bin/bash
TYPE=abc
TIME=205
g++ -g -std=c++17 -Wall -O2 -D_GLIBCXX_DEBUG ./atcoder/$TYPE/$TIME/$1.cpp
echo compiled
./a.out
