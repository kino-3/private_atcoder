#!/bin/bash
source ./config.sh
g++ -g -std=c++17 ./atcoder/$TYPE/$TIME/$1.cpp -o ./a1.out
g++ -g -std=c++17 ./atcoder/$TYPE/$TIME/$2.cpp -o ./a2.out
echo compiled

# テスト
run=1
while true; do
    echo run $((run++))
    python ./atcoder/$TYPE/$TIME/$3.py > input.txt
    ans1=$(./a1.out < input.txt)
    ans2=$(./a2.out < input.txt)
    if [[ $ans1 != $ans2 ]]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        break
    fi
done