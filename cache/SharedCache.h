#include "Cache.h"
#pragma once

struct SharedCacheLine {
  std::string data;
  std::string memory_address;
  int count;
};

class SharedCache : Cache {
public:
	SharedCache(Memory* memory);
	~SharedCache();
  // TODO: add differences from core cache
};

