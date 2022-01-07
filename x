#!/bin/bash
TYPE=abc
TIME=200
g++ -g -D_DEBUG -std=c++17 -Wall -O2 -D_GLIBCXX_DEBUG ./atcoder/$TYPE/$TIME/$1.cpp
# distance + lower_bound が使いたいとき?
# g++ -g -D_DEBUG -std=c++17 -Wall -O2 ./atcoder/$TYPE/$TIME/$1.cpp
echo compiled
./a.out
