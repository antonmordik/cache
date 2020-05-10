#include "Cache.h"
#include <filesystem>
#include <iostream>

// Common params
constexpr auto ELEMENT_SIZE = 4;

// Cache default params
constexpr auto LINE_SIZE = 8;
constexpr auto LINES_COUNT = 64;
constexpr auto SLOTS_IN_SETS_COUNT = 4;

Cache::Cache(Memory* memory) {
  this->linesCount = LINES_COUNT;
  for (int tag = 0; tag < LINES_COUNT; tag++) {
    this->lines.insert(std::pair<std::string, CacheLine>(to_hex_string(tag), { "", "", 0 }));
  }
  this->memory = memory;
}

std::string Cache::insert(std::string data) {
  using namespace std;
  string memory_address = memory->insert(data);
  string inserted_tag = "";
  for (int tag = 0; tag < this->linesCount; tag++) {
    if (this->lines.at(to_hex_string(tag)).data == "") {
      inserted_tag = to_hex_string(tag);
      this->lines.at(inserted_tag).data = data;
      this->lines.at(inserted_tag).count = 0;
      this->lines.at(inserted_tag).memory_address = memory_address;
      break;
    }
  }

  if (inserted_tag == "") {
    int min_count = INFINITY;
    int min_tag = 0;
    for (int tag = 0; tag < this->linesCount; tag++) {
      if (this->lines.at(to_hex_string(tag)).count < min_count) {
        min_count = this->lines.at(to_hex_string(tag)).count;
        min_tag = tag;
      }
    }
    inserted_tag = to_hex_string(min_tag);
    this->lines.at(inserted_tag).data = data;
    this->lines.at(inserted_tag).count = 0;
    this->lines.at(inserted_tag).memory_address = memory_address;
  }

  return inserted_tag;
}

std::string Cache::replace(std::string tag, std::string data) {
  std::string old_data = this->lines.at(tag).data;
  this->lines.at(tag).data = data;
  this->lines.at(tag).count += 1;
  return old_data;
}

void Cache::clear() {
  this->lines.clear();
}

Cache::~Cache() {
  this->clear();
  delete this->memory;
}
