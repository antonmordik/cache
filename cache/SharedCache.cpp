#include "SharedCache.h"



SharedCache::SharedCache(Memory* memory): Cache(memory, 64 * 4) { }


SharedCache::~SharedCache() {
  this->lines.clear();
  delete this->memory;
}

// TODO: add differences from core cache
