# play_with_dramsim3
MEMORY CENTRIC SYSTEMS FOR AI(CSI6207-01) Lecture at Yonsei(20-1)

## Setup & Build & Run
~~~bash
# Setup DRAMsim3 to shared library
./dramsim3.sh
# Build src
make
# Run main
./run.sh
~~~

## Final Project Instruction
[DRAMsim3](https://github.com/umd-memsys/DRAMsim3) is a cycle-accurate DRAM simulator, which faithfully models almost all aspects of modern DRAM, including the timings that we have covered, power consumption, etc.

'traces' are from ResNet-18 training.

### 1. See the effect of address mapping and other parameters (★)

This is an option if you wish to put in the minimum of minimum effort. 
You can already run the provided traces with no modifications to the DRAMsim.
change the parameters from the configurations file, especially the address mapping, and see the performance difference.
I hope your report includes a good interpretation of those results.

### 2. Create a simple closed-loop trace simulator (★★)

A downside of trace-based simulation is it cannot simulate the real slowdown of an application, since the requests will arrive at the designated cycle no matter what.
You can create a trace player which also simulates stall cycles, with a fixed number of load buffers.
For example, if you have only one load buffer, than each time a request is made, the latency should be added to the next request's arrival time.

### 3. Attach an existing simulator (★★★)

There are many timing simulators out there in the world, such as gem5 (https://www.gem5.org/), snipersim (https://snipersim.org//w/The_Sniper_Multi-Core_Simulator), or zsim (https://github.com/s5z/zsim)
if you want to try NPUs, one repo I have found is : https://github.com/pfpsim/simple-npu (no guarantee on this one)

### 4. Implement a scheduler  (★★★)

DRAMsim implements a simple FCFS scheduler. 
You can try implementing other schedulers such as FR-FCFS, parbs, etc.

### 5. Reproduce a paper (★★★)

There are many papers (staged read: https://ieeexplore.ieee.org/abstract/document/6168943) (bank group level parallelism https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=7845573) that you can implement on top of DRAMsim.

<br>choose one and have fun

<br>If you do not want to use DRAMsim3, there are some alternatives, 
- McSimA+ https://bitbucket.org/scale_snu/mcsim_public/src/master/
- DRAMsim2 https://github.com/umd-memsys/DRAMSim2
- Ramulator https://github.com/CMU-SAFARI/ramulator
- Ramulator-pim https://github.com/CMU-SAFARI/ramulator-pim
