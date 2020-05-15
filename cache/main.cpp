#include <iostream>
#include "Database.h"
#include "Caches.h"
#include "Matrix.h"

void main()
{
  Database test;
  std::cout << "Setup of memory started." << std::endl;
  Memory memory;
  std::cout << "Setup of memory ended" << std::endl;
  SharedCache* shared_cache = new SharedCache(&memory);
  std::cout << "Setup of cache 1 started." << std::endl;
  LocalCache* first_core_cache = new LocalCache(&memory, shared_cache, 1);
  std::cout << "Setup of cache " << first_core_cache->id << "ended." << std::endl;
  std::cout << "Setup of cache 2 started." << std::endl;
  LocalCache* second_core_cache = new LocalCache(&memory, shared_cache, 2);
  std::cout << "Setup of cache " << second_core_cache->id << "ended.\n";
  Matrix matrix = Matrix(&memory, 10);
  std::cout << memory.to_string();
}
