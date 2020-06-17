#!/bin/bash

cd ext
# Clone DRAMsim3 master branch
git clone https://github.com/umd-memsys/DRAMsim3.git
cp configuration_for_dramsim3.cc ./DRAMsim3/src
cd DRAMsim3
# Make a DRAMsim3 library(Shared)
make libdramsim3.so
