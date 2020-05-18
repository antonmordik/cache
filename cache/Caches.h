#include "Memory.h"
#pragma once

struct Line {
  int data; // data of line
  std::string memory_address; // location of data in memory
  unsigned int last_use; // timestamp of last usage of line

  Line() {
    this->data = -1;
    this->last_use = 0;
    this->memory_address = "";
  }
};

struct SharedCacheLine : Line {
  int cache_id;
  std::string cache_tag;
  SharedCacheLine(int data, std::string memory_address, int cache_id, std::string cache_tag) {
    this->data = data;
    this->memory_address = memory_address;
    this->last_use = 0; // Now
    this->cache_id = cache_id;
    this->cache_tag = cache_tag;
  }
};

class Cache {
public:
  Cache(Memory* memory, int lines_count, int id);
  ~Cache();
  unsigned int id; // identifier of cache
  std::string insert(int data, std::string address); // adding data to cache (if cache fulled - replaced less used line), returns tag of new line
  int replace(std::string tag, int data); // replacing data on provided tag; returns old data
  int read(std::string tag); // accesing to cache line
  std::string get_tag(std::string address);
  void clear(); // clearing all cache lines
protected:
  int lines_count; // amount of lines in cache
  Memory* memory; // link to memory
  std::map<std::string, Line*> lines; // lines with data
};

class SharedCache : public Cache {
public:
  SharedCache(Memory* memory);
  ~SharedCache();
  std::string insert(int data, std::string memory_address, int cache_id, std::string cache_tag);
private:
  std::map<std::string, SharedCacheLine*> lines;
};

class LocalCache : public Cache {
public:
  LocalCache(Memory* memory, SharedCache* shared_cache, int id);
  ~LocalCache();
private:
  SharedCache* shared_cache;
};
