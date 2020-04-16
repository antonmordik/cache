#include "Cache.h"
#pragma once

class Core
{
public:
	Core(int num);
  ~Core();
private:
  int number;
  Cache* l1;
  Cache* l2;
};

