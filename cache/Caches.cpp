#include "Caches.h"
#include <iostream>

double get_now_in_milliseconds() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Cache::Cache(Memory* memory, int lines_count, int id = -1) {
  this->id = id;
  this->lines_count = lines_count;
  for (int tag = 0; tag < lines_count; tag++) {
    this->lines.insert(std::pair<std::string, Line*>(
      to_hex_string(tag),
      (id == -1 ? new SharedCacheLine() : new Line()))
    );
  }
  this->memory = memory;
}

std::string Cache::insert(int data, std::string address = "") {
  using namespace std;
  string memory_address;
  if (address == "") {
    memory_address = memory->insert(data);
  }
  else {
    memory_address = address;
  }

  string inserted_tag = "";
  for (int tag = 0; tag < this->lines_count; tag++) {
    if (this->lines.at(to_hex_string(tag))->data == -1) {
      inserted_tag = to_hex_string(tag);
      this->lines.at(inserted_tag)->data = data;
      this->lines.at(inserted_tag)->last_use = get_now_in_milliseconds();
      this->lines.at(inserted_tag)->memory_address = memory_address;
      memory_address = this->memory->replace(memory_address, data);
      break;
    }
  }

  if (inserted_tag == "") {
    double min_time = INFINITY;
    int min_tag = 0;
    for (int tag = 0; tag < this->lines_count; tag++) {
      if (this->lines.at(to_hex_string(tag))->last_use < min_time) {
        min_time = this->lines.at(to_hex_string(tag))->last_use;
        min_tag = tag;
      }
    }
    inserted_tag = to_hex_string(min_tag);
    this->lines.at(inserted_tag)->data = data;
    this->lines.at(inserted_tag)->last_use = get_now_in_milliseconds();
    this->lines.at(inserted_tag)->memory_address = memory_address;
    memory_address = this->memory->replace(memory_address, data);
  }

  return inserted_tag;
}

int Cache::replace(std::string tag, int data) {
  int old_data = this->lines.at(tag)->data;
  this->lines.at(tag)->data = data;
  this->lines.at(tag)->last_use = get_now_in_milliseconds();
  return old_data;
}

int Cache::read(std::string tag) {
  this->lines.at(tag)->last_use = get_now_in_milliseconds();
  return this->lines.at(tag)->data;
}

std::string Cache::get_tag(std::string address, bool shared_cache) {
  for (const auto& pair : this->lines) {
    if (pair.second->memory_address == address) {
      return pair.first;
    }
  }
  return "";
}

void Cache::clear() {
  this->lines.clear();
}

std::string Cache::to_string() {
  std::string result = "";
  for (const auto& pair : this->lines) {
    result += "[" + pair.first + "] - [" + pair.second->memory_address + "] - " + std::to_string(pair.second->data) + "\n";
  }
  return result;
}

Cache::~Cache() {
  this->clear();
  delete this->memory;
}

SharedCache::SharedCache(Memory* memory) : Cache(memory, 64 * 4) { }

LocalCache::LocalCache(
  Memory* memory,
  SharedCache* shared_cache,
  int id
  ): Cache(memory, 64, id) {
  this->shared_cache = shared_cache;
}
