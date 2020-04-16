#include "Core.h"
#include <iostream>

Core::Core(int num)
{
  this->number = num;
  this->l1 = new Cache(CacheType::L1);
  this->l2 = new Cache(CacheType::L2);
  // TODO: remove log
  std::cout << this->l1->toString();
  std::cout << this->l2->toString() << std::endl;
}

Core::~Core()
{
  delete this->l1;
  delete this->l2;
}

