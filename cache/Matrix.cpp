#include "Matrix.h"
#include <stdlib.h>
#include <time.h>  

Matrix::Matrix(Memory* memory, unsigned int size) {
  srand((unsigned int)time(NULL));
  using namespace std;
  this->memory = memory;
  this->size = size;
  this->matrix = new string*[size];
  for (unsigned int i = 0; i < size; i++) {
    this->matrix[i] = new string[size];
    for (unsigned int j = 0; j < size; j++) {
      if (i == j) {
        this->matrix[i][j] = this->memory->insert(0); // setting 0 to avoid self entering
      } else {
        this->matrix[i][j] = this->memory->insert(rand() % 99 + 1); // generating random number in [1..99]
      }
    }
  }
}


Matrix::~Matrix() { 
  delete[] this->matrix;
}
