#ifndef __MEM_CTRLER_H__
#define __MEM_CTRLER_H__

#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <string>
/* DRAMsim3 headers */
#include <common.h>
#include <dramsim3.h>

/* Memory Request Structure */
struct mem_request_t {
	mem_request_t(uint64_t m_addr)
    : addr(m_addr) {}
	uint64_t addr;
};

/* Memory Controller Base */ 
class mem_ctrler_base_t {
public:
    mem_ctrler_base_t(const std::string& m_config_file, const std::string& m_output_dir) 
    : clk(0) {
        mem = dramsim3::GetMemorySystem(m_config_file, m_output_dir,
                            std::bind(&mem_ctrler_base_t::read_callback, this, std::placeholders::_1),
                            std::bind(&mem_ctrler_base_t::write_callback, this, std::placeholders::_1));
    }
    virtual ~mem_ctrler_base_t() {};
    virtual void tick() = 0;
    virtual void read_callback(uint64_t m_addr) = 0;
    virtual void write_callback(uint64_t m_addr) = 0;
    void print_stats() { mem->PrintStats(); }

protected:
    dramsim3::MemorySystem *mem;
    uint64_t clk;
};

/* Trace Memory Controller */ 
class trace_mem_ctrler_t : public mem_ctrler_base_t {
public:
    trace_mem_ctrler_t(const std::string& m_config_file, const std::string& m_output_dir,
                        const std::string& m_trace_file);
    ~trace_mem_ctrler_t() { trace_file.close(); }
    void tick();
    void read_callback(uint64_t m_addr) { return; }
    void write_callback(uint64_t m_addr) { return; }
    
private:
    bool get_next;
    std::ifstream trace_file;
	dramsim3::Transaction trans;
};

/* Gem5 Memory Controller */ 
class gem5_mem_ctrler_t : public mem_ctrler_base_t {
public:
    gem5_mem_ctrler_t(const std::string& m_config_file, const std::string& m_output_dir);
    ~gem5_mem_ctrler_t() {}
    void tick();
    void read_callback(uint64_t m_addr) { return; }
    void write_callback(uint64_t m_addr) { return; }
    void load_requests(const std::list<mem_request_t> &m_mem_requests) { mem_requests = m_mem_requests; }

private:
    std::list<mem_request_t> mem_requests;
};

#endif