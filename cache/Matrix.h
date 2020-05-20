#include "System.h"
#include "Logger.h"
#pragma once

class Matrix {
private:
  std::string** matrix;
  System* system;
  Logger* logger;
  unsigned int size;
public:
	Matrix(System* system, unsigned int size);
	~Matrix();
  int get(unsigned int i, unsigned int j); // getting element on [i][j] position, source: Memory
  int get(int core_id, unsigned int i, unsigned int j); // getting element on [i][j] position, source LocalCache -> SharedCache -> Memory
  void set(unsigned int i, unsigned int j, int value); // setting value to [i][j] position, source: Memory
  void set(int core_id, unsigned int i, unsigned int j, int value); // setting value to [i][j] position, source: LocalCache -> SharedCache -> Memory
  unsigned int get_size();
  unsigned int get_number_of_cores();
  std::string to_string();
  std::string to_JSON();
  Logger* get_logger();
  System* get_system();
};

