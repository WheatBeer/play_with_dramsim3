#include "trace_cpu.h"

trace_cpu_t::trace_cpu_t(const std::string& config_file,
                             const std::string& output_dir,
                             const std::string& trace_file)
    : cpu_t(config_file, output_dir) {
    trace_file_.open(trace_file);
    if (trace_file_.fail()) {
        std::cerr << "Trace file does not exist" << std::endl;
		exit(1);
    }
}

void trace_cpu_t::tick() {
    memory_system_->ClockTick();
    if (!trace_file_.eof()) {
        if (get_next_) {
            get_next_ = false;
            trace_file_ >> trans_;
        }
        if (trans_.added_cycle <= clk_) {
            get_next_ = memory_system_->WillAcceptTransaction(trans_.addr,
                                                             trans_.is_write);
            if (get_next_) {
                memory_system_->AddTransaction(trans_.addr, trans_.is_write);
            }
        }
    }
    clk_++;
    return;
}
