#include "Caches.h"

Cache::Cache(Memory* memory, int lines_count, int id = -1) {
  this->id = id;
  this->lines_count = lines_count;
  for (int tag = 0; tag < lines_count; tag++) {
    this->lines.insert(std::pair<std::string, Line*>(to_hex_string(tag), new Line()));
  }
  this->memory = memory;
}

std::string Cache::insert(int data, std::string address = "") {
  // TODO: add write incrementer
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
      this->lines.at(inserted_tag)->last_use = 0; // TODO: set current date in milliseconds
      this->lines.at(inserted_tag)->memory_address = memory_address;
      break;
    }
  }

  if (inserted_tag == "") {
    int min_time = INFINITY;
    int min_tag = 0;
    for (unsigned int tag = 0; tag < this->lines_count; tag++) {
      if (this->lines.at(to_hex_string(tag))->last_use < min_time) {
        min_time = this->lines.at(to_hex_string(tag))->last_use;
        min_tag = tag;
      }
    }
    inserted_tag = to_hex_string(min_tag);
    this->lines.at(inserted_tag)->data = data;
    this->lines.at(inserted_tag)->last_use = 0; // TODO: set current date in milliseconds
    this->lines.at(inserted_tag)->memory_address = memory_address;
  }

  return inserted_tag;
}

int Cache::replace(std::string tag, int data) {
  // TODO: add write incrementer
  int old_data = this->lines.at(tag)->data;
  this->lines.at(tag)->data = data;
  this->lines.at(tag)->last_use = 0; // TODO: set current date in milliseconds
  return old_data;
}

int Cache::read(std::string tag) {
  // TODO: add hit or miss incrementer
  this->lines.at(tag)->last_use = 0; // TODO: set current date in milliseconds
  return this->lines.at(tag)->data;
}

std::string Cache::get_tag(std::string address) {
  for (unsigned int tag = 0; tag < this->lines_count; tag++) {
    if (this->lines.at(to_hex_string(tag))->memory_address == address) {
      return to_hex_string(tag);
    }
  }
  return "";
}

void Cache::clear() {
  this->lines.clear();
}

Cache::~Cache() {
  this->clear();
  delete this->memory;
}

SharedCache::SharedCache(Memory* memory) : Cache(memory, 64 * 4) { 
  for (int tag = 0; tag < this->lines_count; tag++) {
    // TODO: fix this
    this->lines.insert(
      std::pair<std::string, SharedCacheLine*>(
        to_hex_string(tag),
        new SharedCacheLine(-1, "", -1, "")
      )
    );
  }
}

std::string SharedCache::insert(int data, std::string memory_address, int cache_id, std::string cache_tag) {
  using namespace std;
  string inserted_tag = "";
  for (int tag = 0; tag < this->lines_count; tag++) {
    if (this->lines.at(to_hex_string(tag))->data == -1) {
      inserted_tag = to_hex_string(tag);
      this->lines.at(inserted_tag)->data = data;
      this->lines.at(inserted_tag)->last_use = 0; // TODO: set current date in milliseconds
      this->lines.at(inserted_tag)->memory_address = memory_address;
      this->lines.at(inserted_tag)->cache_id = cache_id;
      this->lines.at(inserted_tag)->cache_tag = cache_tag;
      break;
    }
  }

  if (inserted_tag == "") {
    int min_time = INFINITY;
    int min_tag = 0;
    for (unsigned int tag = 0; tag < this->lines_count; tag++) {
      if (this->lines.at(to_hex_string(tag))->last_use < min_time) {
        min_time = this->lines.at(to_hex_string(tag))->last_use;
        min_tag = tag;
      }
    }
    inserted_tag = to_hex_string(min_tag);
    this->lines.at(inserted_tag)->data = data;
    this->lines.at(inserted_tag)->last_use = 0; // TODO: set current date in milliseconds
    this->lines.at(inserted_tag)->memory_address = memory_address;
  }

  return inserted_tag;
}

LocalCache::LocalCache(Memory* memory, SharedCache* shared_cache, int id): Cache(memory, 64, id) {
  this->shared_cache = shared_cache;
}
