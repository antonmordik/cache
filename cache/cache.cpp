#include "Cache.h"
#include <filesystem>

// Common params
constexpr auto ELEMENT_SIZE = 4;

// Cache default params
constexpr auto LINE_SIZE = 8;
constexpr auto LINES_COUNT = 64;
constexpr auto SETS_COUNT = 4;
constexpr auto SLOTS_IN_SETS_COUNT = 4;

Cache::Cache()
{
  this->linesCount = LINES_COUNT * 2;
  this->lineSize = LINE_SIZE;
  this->setsCount = SETS_COUNT * 2;
  this->slotsCount = SLOTS_IN_SETS_COUNT;
  this->lines = new CacheLine[this->linesCount];
}

std::string Cache::toString() {
  using namespace std;
  return "Cache: Lines count: " + to_string(this->linesCount) + "; Line size: " + to_string(this->lineSize) + ".\n";
}

CacheLine Cache::pop(int index) {
  CacheLine result = this->lines[index];
  delete &this->lines[index];
  return result;
}

CacheLine Cache::pop(std::string data) {
  for (int i = 0; i < this->linesCount; i += 1) {
    if (this->lines[i].data == data) {
      CacheLine result = this->lines[i];
      delete& this->lines[i];
      return result;
    }
  }
}

int Cache::push(std::string data) {
  int insertedIndex = -1;
  for (int i = 0; i < this->linesCount; i += 1) {
    if (&this->lines[i]) {
      CacheLine line = CacheLine(std::to_string(i / this->setsCount), data);
      this->lines[i] = line;
    }
  }
}

int Cache::findLessUsedLine() {
  int minIndex = -1;
  int minCount = INFINITY;
  for (int i = 0; i < this->linesCount; i += 1) {
    if (*&this->lines[i].count < minCount) {
      minCount = *&this->lines[i].count;
      minIndex = i;
    }
  }
  return minIndex;
}

void Cache::clear() {
  delete this->lines;
}

Cache::~Cache()
{
  delete this->lines;
}
