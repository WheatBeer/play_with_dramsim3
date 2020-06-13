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
	mem_request_t(uint64_t m_addr, bool m_is_write)
    : is_write(m_is_write), addr(m_addr) {}
	bool is_write;
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
					   const std::string& m_trace_file)
	: mem_ctrler_base_t(m_config_file, m_output_dir), 
	  get_next(true), trace_cnt(0), callback_cnt(0) {
		trace_file.open(m_trace_file);
		if(trace_file.fail()) { std::cerr << "Trace file does not exist" << std::endl; exit(1); }
	}
    ~trace_mem_ctrler_t() { mem->GetQueueSize(); trace_file.close(); }
    void tick();
    void read_callback(uint64_t m_addr) { callback_cnt++; return; }
    void write_callback(uint64_t m_addr) { callback_cnt++; return; }
	bool is_end() { return trace_file.eof() && trace_cnt == callback_cnt; }
    
private:
    bool get_next;
	size_t trace_cnt;
	size_t callback_cnt;
    std::ifstream trace_file;
	dramsim3::Transaction trans;
};

/* Timing Memory Controller */ 
class timing_mem_ctrler_t : public mem_ctrler_base_t {
public: 
	timing_mem_ctrler_t(const std::string& m_config_file, const std::string& m_output_dir)
	: mem_ctrler_base_t(m_config_file, m_output_dir), 
	  send_cnt(0), callback_cnt(0) {}
    ~timing_mem_ctrler_t() {}
    void tick() { mem->ClockTick(); clk++; return; }
    void read_callback(uint64_t m_addr);
    void write_callback(uint64_t m_addr);
	bool will_accept_transaction(uint64_t addr_, bool is_write_) const;
	void add_transaction(uint64_t addr_, bool is_write_);
	bool is_end() { return send_cnt == callback_cnt && queue.size() == 0; }

private:
	size_t send_cnt;
	size_t callback_cnt;
    std::list<mem_request_t> queue;
};

#endif
