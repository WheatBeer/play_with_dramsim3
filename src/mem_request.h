#ifndef __MEM_REQUEST_H__
#define __MEM_REQUEST_H__

#include <cstdint>

struct mem_request_t {
  mem_request_t(uint64_t address)
    : address(address) {}

  uint64_t address;
};

#endif
