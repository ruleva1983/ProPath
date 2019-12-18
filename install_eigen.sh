#!/usr/bin/env bash

#Run this script from the same folder

git clone https://github.com/libigl/eigen.git
cd eigen/
cp -r ./Eigen/ ../third-party/
cd ..
rm -rf eigen/
