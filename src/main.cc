#include <cstring>
#include <errno.h> 
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h> 
#include <sys/types.h> 
/* src headers */
#include "mem_ctrler.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc != 1) {
        cerr << "Usage: " << argv[0] << endl;
        exit(1);
    }

	/* Set DRAMsim3 config and trace */
	string dram_cfg = "DDR4_8Gb_x8_2400.ini";
	string dram_cfg_path = "./DRAMsim3/configs/" + dram_cfg;
	string trace_name = "trace1.txt";	
	string trace_path = "./traces/" + trace_name;

    /* Make 'stats' directory to save DRAMsim3 outputs */
	if(mkdir("./stats", 0776) == -1 && errno != EEXIST) { 
        std::cout << strerror(errno) << " directory create error" << std::endl; 
    }
	else {
        /* Trace Memory Controller Test */
		trace_mem_ctrler_t *trace_mem_ctrler = new trace_mem_ctrler_t(dram_cfg_path, "./stats", trace_path);
		size_t cycles = 100000;
		for(size_t clk = 0; clk < cycles; clk++) {
			trace_mem_ctrler->tick();
		}
		trace_mem_ctrler->print_stats();
		delete trace_mem_ctrler;

        /* Gem5 Memory Controller Test */
        gem5_mem_ctrler_t *gem5_mem_ctrler = new gem5_mem_ctrler_t(dram_cfg_path, "./stats");
        /* TODO: Gem5 */
        delete gem5_mem_ctrler;
	}	

	return 0;
}
