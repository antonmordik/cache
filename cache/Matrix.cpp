#include "Matrix.h"
#include <stdlib.h>
#include <time.h>  

Matrix::Matrix(System* system, unsigned int size) {
  srand((unsigned int)time(NULL));
  using namespace std;
  this->system = system;
  this->size = size;
  this->matrix = new string*[size];
  Memory* memory = this->system->get_memory();
  for (unsigned int i = 0; i < size; i++) {
    this->matrix[i] = new string[size];
    for (unsigned int j = 0; j < size; j++) {
      if (i == j) {
        this->matrix[i][j] = memory->insert(0); // setting 0 to avoid self entering
      } else {
        this->matrix[i][j] = memory->insert(rand() % 99 + 1); // generating random number in [1..99]
      }
    }
  }
}

Matrix::~Matrix() { 
  delete[] this->matrix;
}

int Matrix::get(unsigned int i, unsigned int j) {
  if (i >= this->size || j >= this->size) { return -1; }
  std::string address = this->matrix[i][j];
  return this->system->get_memory()->read(address);
}

int Matrix::get(int core_id, unsigned int i, unsigned int j) {
  LocalCache* target_cache = this->system->get_local_cache(core_id);
  SharedCache* shared_cache = this->system->get_shared_cache();
  Memory* memory = this->system->get_memory();
  std::string address = this->matrix[i][j];
  std::string tag = target_cache->get_tag(address);
  if (tag == "") {
    // miss happened
    tag = shared_cache->get_tag(address); // trying to find line in shared cache
    if (tag == "") {
      // shared cache miss happened => getting from memory
      return memory->read(address);
    }
    return shared_cache->read(tag);
  }
  return target_cache->read(tag);
}

void Matrix::set(unsigned int i, unsigned int j, int value) {
  if (i >= this->size || j >= this->size) { return; }
  std::string address = this->matrix[i][j];
  std::string result = this->system->get_memory()->replace(address, value);
}

void Matrix::set(int core_id, unsigned int i, unsigned int j, int value) {
  using namespace std;
  LocalCache* target_cache = this->system->get_local_cache(core_id);
  SharedCache* shared_cache = this->system->get_shared_cache();
  Memory* memory = this->system->get_memory();
  string address = this->matrix[i][j];

  string existed_tag = target_cache->get_tag(address);
  string inserted_tag;

  if (existed_tag == "") {
    inserted_tag = target_cache->insert(value, address);
    return;
  } else {
    inserted_tag = existed_tag;
    target_cache->replace(inserted_tag, value);
  }
}

unsigned int Matrix::get_size() {
  return this->size;
}

unsigned int Matrix::get_number_of_cores() {
  return this->system->get_number_of_cores();
}

std::string Matrix::to_string() {
  Memory* memory = this->system->get_memory();
  std::string result = "";
  for (unsigned int i = 0; i < size; i++) {
    for (unsigned int j = 0; j < size; j++) {
      result += std::to_string(memory->read(this->matrix[i][j]))  + " ";
    }
    result += "\n";
  }
  return result;
}
