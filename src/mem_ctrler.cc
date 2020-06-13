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

/* Timing Memory Controller */ 
void timing_mem_ctrler_t::tick() {
    mem->ClockTick();
    if(!trace_file.eof()) {
        if(buffer.size() < buffer_size) {
			dramsim3::Transaction trans;
            trace_file >> trans;
			trace_cnt++;
            buffer.push_back(std::make_pair(false, trans));
		}
	}
	for(auto it = buffer.begin(); it != buffer.end(); ++it) {
		if(!it->first) {
			if(it->second.added_cycle <= clk && mem->WillAcceptTransaction(it->second.addr, it->second.is_write)) {
				it->first = true;
				mem->AddTransaction(it->second.addr, it->second.is_write);
			}
		}	
	}
    clk++;
    return;
}

void timing_mem_ctrler_t::read_callback(uint64_t m_addr) {
    for(auto it = buffer.cbegin(); it != buffer.cend(); ++it) {
        if(it->second.addr == m_addr) {
			callback_cnt++;
            buffer.erase(it);
            return;
        }
    }
}

void timing_mem_ctrler_t::write_callback(uint64_t m_addr) {
    for(auto it = buffer.cbegin(); it != buffer.cend(); ++it) {
        if(it->second.addr == m_addr) {
			callback_cnt++;
            buffer.erase(it);
            return;
        }
    }
}
