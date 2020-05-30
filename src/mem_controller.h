#ifndef __MEMORY_CONTROLLER_H__
#define __MEMORY_CONTROLLER_H__
#include <list>
#include <string>
#include <dramsim3.h>
#include "mem_request.h"

class mem_controller_t {
public:
    mem_controller_t(std::string config_file, std::string output_dir);
    ~mem_controller_t();
    
    void send_request(uint64_t address, bool is_write);
    bool will_accept_transaction(uint64_t address, bool is_write);
    void tick();

    void read_callback(uint64_t address);
    void write_callback(uint64_t address);

    // Print stats.
    void print_stats();
    // Print configs.
    void print_configs();

private:
    dramsim3::MemorySystem *mem;
    std::list<mem_request_t> pending_requests;
};

#endif
