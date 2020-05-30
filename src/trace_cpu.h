#ifndef __TRACE_CPU_H__
#define __TRACE_CPU_H__

#include <fstream>
#include <functional>
#include <random>
#include <string>
/* DRAMsim3 headers */
#include <common.h>
#include <dramsim3.h>

class cpu_t {
public:
	cpu_t(const std::string& config_file, const std::string& output_dir) : clk_(0) { 
		memory_system_ = dramsim3::GetMemorySystem(config_file, output_dir,
					  std::bind(&cpu_t::read_callback, this, std::placeholders::_1),
					  std::bind(&cpu_t::write_callback, this, std::placeholders::_1));
}
	virtual ~cpu_t() {}
	virtual void tick() = 0;
    void read_callback(uint64_t address) { return; }
    void write_callback(uint64_t address) { return; }
    void print_stats() { memory_system_->PrintStats(); }

protected:
	dramsim3::MemorySystem *memory_system_;
    uint64_t clk_;
};

class trace_cpu_t : public cpu_t {
public:
    trace_cpu_t(const std::string& config_file, const std::string& output_dir,
                  const std::string& trace_file);
    ~trace_cpu_t() { trace_file_.close(); }
    void tick() override;

private:
    std::ifstream trace_file_;
	dramsim3::Transaction trans_;
    bool get_next_ = true;
};

#endif
