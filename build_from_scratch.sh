#!/usr/bin/env bash

rm build/ -rf
mkdir build
cd build
cmake ..
make
