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
    string dram_cfg_path = "./ext/DRAMsim3/configs/" + dram_cfg;
    string output_dir = "./stats";

    /* Make 'stats' directory to save DRAMsim3 outputs */
    if(mkdir(output_dir.c_str(), 0776) == -1 && errno != EEXIST) { 
        std::cout << strerror(errno) << " Directory create error" << std::endl; 
    }
    else {
        unsigned num_traces = 8;
        for(unsigned i = 0; i < num_traces; i++) {
            if(i != 6) {
                string trace_name = "trace" + to_string(i + 1);
                string output_path = output_dir + "/fcfs_" + trace_name;
                string trace_path = "./traces/" + trace_name + ".txt";
                /* Trace Memory Controller Test */
                trace_mem_ctrler_t *trace_mem_ctrler = new trace_mem_ctrler_t(dram_cfg_path, output_path, trace_path);
                while(!trace_mem_ctrler->is_end()) { 
                    trace_mem_ctrler->tick(); 
                }
                trace_mem_ctrler->print_stats();
                delete trace_mem_ctrler;
            }
        }
    }	
    return 0;
}
