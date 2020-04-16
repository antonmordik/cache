#include <string>
#pragma once

enum CacheType
{
  L1 = 1, L2 = 2
};

class Cache
{
public:
	Cache(CacheType type);
	~Cache();
  std::string toString();
private:
  CacheType type;
  int lineSize; // amount of bytes in line
  int linesCount; // amount of lines in cache
  int setsCount; // amount of sets in cache
  int slotsCount; // amount of slots in set

  // TODO: make push and pop method to manipulate data from Core
};

