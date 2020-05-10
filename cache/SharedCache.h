#include "Memory.h"
#pragma once

struct SharedCacheLine {
  std::string data;
  std::string memory_address;
  int count;
};

class SharedCache
{
public:
	SharedCache(Memory* memory);
	~SharedCache();
private:
  Memory* memory;
  // storage parameters
  std::map<std::string, SharedCacheLine> lines; // list of lines in shared cache
  int linesCount; // amount of lines in cache


};

