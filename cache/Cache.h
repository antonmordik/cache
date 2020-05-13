#include "Memory.h"
#pragma once

struct CacheLine {
  std::string data; // data of line
  std::string memory_address; // location of data in memory
  int count; // count of use
};

class Cache
{
public:
	Cache(Memory* memory, int linesCount);
	~Cache();
  std::string insert(std::string data); // adding data to cache (if cache fulled - replaced less used line), returns tag of new line
  std::string replace(std::string tag, std::string data); // replacing data on provided tag; returns old data
  std::string read(std::string tag);
  void clear(); // clearing all cache lines
protected:
  int linesCount; // amount of lines in cache
  Memory* memory; // link to memory
  std::map<std::string, CacheLine> lines; // lines with data
};

