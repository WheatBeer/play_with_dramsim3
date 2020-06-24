#include "mem_ctrler.h"

/* Trace Memory Controller */ 
void trace_mem_ctrler_t::tick() {
    mem->ClockTick();
    if(!trace_file.eof()) {
        if(get_next) {
            get_next = false;
            trace_file >> trans;
            trace_cnt++;
        }
        if(trans.added_cycle <= clk) {
            get_next = mem->WillAcceptTransaction(trans.addr, trans.is_write);
            if(get_next) {
                mem->AddTransaction(trans.addr, trans.is_write);
            }
        }
    }
    clk++;
    return;
}

bool timing_mem_ctrler_t::will_accept_transaction(uint64_t addr_, bool is_write_) const {
    return mem->WillAcceptTransaction(addr_, is_write_);
}

void timing_mem_ctrler_t::add_transaction(uint64_t addr_, bool is_write_) {
    mem->AddTransaction(addr_, is_write_);
    mem_request_t mem_request(addr_, is_write_);
    queue.push_back(mem_request);
    send_cnt++;
    return;
}

void timing_mem_ctrler_t::read_callback(uint64_t m_addr) {
    for(auto it = queue.cbegin(); it != queue.cend(); ++it) {
        if(it->addr == m_addr) {
            callback_cnt++;
            queue.erase(it);
            return;
        }
    }
}

void timing_mem_ctrler_t::write_callback(uint64_t m_addr) {
    for(auto it = queue.cbegin(); it != queue.cend(); ++it) {
        if(it->addr == m_addr) {
            callback_cnt++;
            queue.erase(it);
            return;
        }
    }
}
