#include "Caches.h"
#include <vector>
#pragma once

class System {
public:
	System(unsigned int number_of_cores);
	~System();
  Memory* get_memory();
  SharedCache* get_shared_cache();
  std::vector<LocalCache*> get_local_caches();
  LocalCache* get_local_cache(unsigned int id);
  unsigned int get_number_of_cores();
private:
  Memory* memory;
  SharedCache* shared_cache;
  unsigned int number_of_cores;
  std::vector<LocalCache*> caches;
};

