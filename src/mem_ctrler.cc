#include "mem_ctrler.h"

trace_mem_ctrler_t::trace_mem_ctrler_t(const std::string& m_config_file, const std::string& m_output_dir,
                                        const std::string& m_trace_file)
: mem_ctrler_base_t(m_config_file, m_output_dir), get_next(true) {
    trace_file.open(m_trace_file);
    if (trace_file.fail()) {
        std::cerr << "Trace file does not exist" << std::endl;
        exit(1);
    }
}

void trace_mem_ctrler_t::tick() {
    mem->ClockTick();
    if (!trace_file.eof()) {
        if (get_next) {
            get_next = false;
            trace_file >> trans;
        }
        if (trans.added_cycle <= clk) {
            get_next = mem->WillAcceptTransaction(trans.addr, trans.is_write);
            if (get_next) {
                mem->AddTransaction(trans.addr, trans.is_write);
            }
        }
    }
    clk++;
    return;
}

gem5_mem_ctrler_t::gem5_mem_ctrler_t(const std::string& m_config_file, const std::string& m_output_dir)
: mem_ctrler_base_t(m_config_file, m_output_dir) {

}

void gem5_mem_ctrler_t::tick() {
    mem->ClockTick();
    /* TODO: Gem5 */
    clk++;
    return;
}