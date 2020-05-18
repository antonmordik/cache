#include <iostream>
#include "Database.h"
#include "System.h"
#include "Matrix.h"
#include "Algorithm.h"

int main() {
  Database test;
  System* system = new System(2);
  Matrix* matrix = new Matrix(system, 4);
  std::cout << matrix->to_string() << std::endl;
  Algorithm::traditional_floyd_warshal(matrix);
  std::cout << matrix->to_string() << std::endl;
  return 0;
}
