#include "Memory.h"
#pragma once

class Cache
{
public:
	Cache();
	~Cache();
  std::string toString();

  int push(std::string data); // adding line to cache
  CacheLine pop(int index); // removing line from cache by index
  CacheLine pop(std::string data); // removing line from cache by data
  void clear(); // clearing cache method
  void transferToMemory(CacheLine line, Memory* memory);

private:

  int lineSize; // amount of bytes in line
  int linesCount; // amount of lines in cache
  int setsCount; // amount of sets in cache
  int slotsCount; // amount of slots in set
  CacheLine *lines; // lines with data
  int findLessUsedLine(); // returning index of less used line in cache
};

