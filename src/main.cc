#include <iostream>
#include <string>

#include "mem_controller.h"

using namespace std;

int main(int argc, char **argv) {
	mem_controller_t mem;
	cout << mem.i << endl;
//    if(argc < 2) {
//        cerr << "Usage: " << argv[0] << " [config]" << endl;
//        exit(1);
//    }
//	string dram_cfg = "DDR4_8Gb_x8_2400.ini";
//	string dram_cfg_path = "DRAMsim3/configs/" + dram_cfg;
//
//    memory_controller_t *mem = new memory_controller_t(dram_cfg_path, ".");
//    mem->send_request(0x100000, true);		// W //    mem->send_request(0x200000, false);		// R
//    mem->send_request(0x300000, true);		// W
//
//    /* To check callback */
//    for (size_t i = 0; i < 10000; i++) {
//      mem->tick();
//    }
//
//    /* End DRAMsim3 test */
//    delete mem;

	cout << "test" << endl;
	return 0;
}
