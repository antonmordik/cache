#include <iostream>
#include "Database.h"
#include "System.h"
#include "Matrix.h"
#include "Algorithm.h"

int main() {
  Database* database = new Database();
  System* system = new System(2);
  Matrix* matrix = new Matrix(system, 10);
  std::cout << "Initial matrix:" << std::endl;
  std::cout << matrix->to_string() << std::endl;
  database->insert(matrix, 0);
  Algorithm::traditional_floyd_warshall(matrix, 10);
  std::cout << "After Floyd-Warshall:" << std::endl;
  std::cout << matrix->to_string() << std::endl;
  database->insert(matrix, 1);
  Logger* matrix_logger = matrix->get_logger();
  std::cout << "Statistics:" << std::endl;
  std::cout << matrix_logger->get_statistics();
  database->insert(matrix->get_logger());
  return 0;
}
