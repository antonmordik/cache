#include "System.h"

System::System(unsigned int number_of_cores) {
  Memory* memory = new Memory();
  this->number_of_cores = number_of_cores;
  this->memory = memory;
  this->shared_cache = new SharedCache(memory);

  for (unsigned int i = 0; i < number_of_cores; i++) {
    this->caches.push_back(new LocalCache(memory, this->shared_cache, i));
  }
}


System::~System() {

}

Memory* System::get_memory() {
  return this->memory;
}

SharedCache* System::get_shared_cache() {
  return this->shared_cache;
}

std::vector<LocalCache*> System::get_local_caches() {
  return this->caches;
}

LocalCache* System::get_local_cache(unsigned int id) {
  if (id >= this->number_of_cores) { return nullptr; }
  return this->caches.at(id);
}

unsigned int System::get_number_of_cores() {
  return this->number_of_cores;
}
