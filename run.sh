#!/usr/bin/bash

g++ -std=c++17 "day$1/cpp/main.cpp" -o "day$1/cpp/day$1.out"
"day$1/cpp/day$1.out" $2