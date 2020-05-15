#include "Memory.h"
#pragma once

class Matrix {
private:
  std::string** matrix;
  Memory* memory;
  unsigned int size;
public:
	Matrix(Memory* memory, unsigned int size);
	~Matrix();
  std::string get(int i, int j); // getting element on [i][j] position
  void set(int i, int j, std::string value); // setting value to [i][j] position
};

