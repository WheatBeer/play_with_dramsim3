#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/ext/DRAMsim3
gdb project 
