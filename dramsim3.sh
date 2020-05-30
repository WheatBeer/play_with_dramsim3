#!/bin/bash

# Clone DRAMsim3 master branch
git clone https://github.com/umd-memsys/DRAMsim3.git
cd DRAMsim3
# Make a DRAMsim3 library(Shared)
make libdramsim3.so
