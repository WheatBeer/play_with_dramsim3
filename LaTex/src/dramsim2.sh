#!/bin/bash

build/X86/gem5.opt configs/example/se.py \
	--cmd=${EXE_FILE_PATH} \
	--cpu-type=TimingSimpleCPU --num-cpu=8 \
	--caches --l2cache \
	--num-l2caches=8 --l1d_size=32kB --l1i_size=32kB --l2_size=512kB \
	--mem-type=DRAMSim2 \

#--debug-flags=DRAMSim2 \
#--caches --l2cache \
#--num-l2caches=1 --l1d_size=32kB --l1i_size=32kB --l2_size=512kB \
#--debug-flags=DRAMsim3 \
#--mem-size=4096MB \
