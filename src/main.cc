#include <cstring>
#include <errno.h> 
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h> 
#include <sys/types.h> 
/* src headers */
#include "mem_controller.h"
#include "mem_request.h"
#include "trace_cpu.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc != 1) {
        cerr << "Usage: " << argv[0] << endl;
        exit(1);
    }

	/* Set DRAMsim3 Config */
	string dram_cfg = "DDR4_8Gb_x8_2400.ini";
	string dram_cfg_path = "./DRAMsim3/configs/" + dram_cfg;
    mem_controller_t *mem = new mem_controller_t(dram_cfg_path, ".");

    mem->send_request(0x100000, true);		// W
    mem->send_request(0x200000, false);		// R
    mem->send_request(0x300000, true);		// W

    /* To check callback */
    for (size_t i = 0; i < 10000; i++) {
      mem->tick();
    }

    delete mem;

	/* Open & Read Trace */
	string trace_name = "trace1.txt";	
	string trace_path = "./traces/" + trace_name;	
	if(mkdir("./stats", 0776) == -1 && errno != EEXIST) { 
        std::cout << strerror(errno) << " directory create error" << std::endl; 
    }
	else {
		cpu_t *trace_cpu = new trace_cpu_t(dram_cfg_path, "./stats", trace_path);
		size_t cycles = 100000;
		for(size_t clk = 0; clk < cycles; clk++) {
			trace_cpu->tick();
		}
		trace_cpu->print_stats();
		delete trace_cpu;
	}	

    /* To check callback */
    for (size_t i = 0; i < 10000; i++) {
      mem->tick();
    }

	return 0;
}
