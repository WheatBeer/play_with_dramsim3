#include <functional>
#include <iostream>

#include "mem_controller.h"

mem_controller_t::mem_controller_t() : i(100) {
}

mem_controller_t::~mem_controller_t() {
}

//mem_controller_t::mem_controller_t(std::string config_file, std::string output_dir) {
//    mem = dramsim3::GetMemorySystem(config_file, output_dir,
//                                std::bind(&mem_controller_t::read_callback, this, std::placeholders::_1),
//                                std::bind(&mem_controller_t::write_callback, this, std::placeholders::_1));
//}
//
//mem_controller_t::~mem_controller_t() {
//    delete mem;
//}
//
//void mem_controller_t::send_request(uint64_t address, bool is_write) {
//    /* Request to DRAM */
//    /* WillAcceptTransaction */
//    mem->AddTransaction(address, is_write);
//    /* Requests in DRAM */
//    pending_requests.push_back(address);
//
//#ifdef MEM_DEBUG
//    std::cout << (is_write ? "Write" : "Read") << " request for address 0x" << std::hex << address << std::dec << std::endl;
//#endif
//}
//
//bool mem_controller_t::will_accept_transaction(uint64_t address, bool is_write) {
//    return mem->WillAcceptTransaction(address, is_write);
//}
//
//
//void mem_controller_t::tick() {
//    mem->ClockTick();
//}
//
//void mem_controller_t::read_callback(uint64_t address) {
//    for (auto it = pending_requests.cbegin(); it != pending_requests.cend(); ++it) {
//        if (it->address == address) {
//            pending_requests.erase(it);
//#ifdef MEM_DEBUG
//            std::cout << "Read callback for address 0x" << std::hex << address << std::dec << std::endl;
//#endif
//            return;
//        }
//    }
//    /* Never be reached: kill simulator */
//}
//
//void mem_controller_t::write_callback(uint64_t address) {
//    for (auto it = pending_requests.cbegin(); it != pending_requests.cend(); ++it) {
//        if (it->address == address) {
//            pending_requests.erase(it);
//#ifdef MEM_DEBUG
//            std::cout << "Write callback for address 0x" << std::hex << address << std::dec << std::endl;
//#endif
//            return;
//        }
//    }
//    /* Never be reached: kill simulator */
//}
//
//void mem_controller_t::load_requests(std::list<mem_request_t> &m_mem_requests) {
//    mem_requests = m_mem_requests;
//}
//
//// Print stats.
//void mem_controller_t::print_stats() {
//    mem->PrintStats();
//}
//// Print configs.
//void mem_controller_t::print_configs() {
//
//}
