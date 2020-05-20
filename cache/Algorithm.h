#include "Matrix.h"

#pragma once
class Algorithm
{
public:
  static void blocked_floyd_warshall(Matrix* matrix);
  static void traditional_floyd_warshall(Matrix* matrix, int timeout_seconds);
};

