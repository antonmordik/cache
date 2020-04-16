#include "Cache.h"
#include <filesystem>

// Common params
constexpr auto ELEMENT_SIZE = 4;

// Cache default params
constexpr auto LINE_SIZE = 8;
constexpr auto LINES_COUNT = 64;
constexpr auto SETS_COUNT = 4;
constexpr auto SLOTS_IN_SETS_COUNT = 4;

Cache::Cache(CacheType type)
{
  this->type = type;
  switch (type)
  {
    case L1:
      this->linesCount = LINES_COUNT;
      this->lineSize = LINE_SIZE;
      this->setsCount = SETS_COUNT;
      this->slotsCount = SLOTS_IN_SETS_COUNT;
      break;
    case L2:
      // Suppose the L2 cache is twice as large as L1
      this->linesCount = LINES_COUNT * 2;
      this->lineSize = LINE_SIZE;
      this->setsCount = SETS_COUNT * 2;
      this->slotsCount = SLOTS_IN_SETS_COUNT;
      break;
    default:
      this->linesCount = 0;
      this->lineSize = 0;
      this->setsCount = 0;
      this->slotsCount = 0;
      break;
  }
}

std::string Cache::toString() {
  using namespace std;
  string type = this->type == CacheType::L1 ? "L1" : this->type == CacheType::L2 ? "L2" : "[Unsupported type]";
  return "Cache " + type + " - Lines count: " + to_string(this->linesCount) + "; Line size: " + to_string(this->lineSize) + ".\n";
}


Cache::~Cache()
{
}
