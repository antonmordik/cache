#include "Matrix.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Matrix::Matrix(System* system, unsigned int size) {
  srand((unsigned int)time(NULL));
  using namespace std;
  this->system = system;
  this->size = size;
  this->matrix = new string*[size];
  Memory* memory = this->system->get_memory();
  this->logger = new Logger();
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
  this->logger->incremet("Read from memory");
  return this->system->get_memory()->read(address);
}

int Matrix::get(int core_id, unsigned int i, unsigned int j) {
  LocalCache* target_cache = this->system->get_local_cache(core_id);
  SharedCache* shared_cache = this->system->get_shared_cache();
  Memory* memory = this->system->get_memory();
  std::string address = this->matrix[i][j];
  std::string tag = target_cache->get_tag(address, false);
  if (tag == "") {
    this->logger->incremet("Miss in " + std::to_string(core_id) + " cache");
    tag = shared_cache->get_tag(address, true);
    if (tag == "") {
      this->logger->incremet("Miss in shared cache");
      return memory->read(address);
    }
    this->logger->incremet("Hit in shared cache");
    return shared_cache->read(tag);
  }
  this->logger->incremet("Hit in " + std::to_string(core_id) + " cache");
  return target_cache->read(tag);
}

void Matrix::set(unsigned int i, unsigned int j, int value) {
  if (i >= this->size || j >= this->size) { return; }
  std::string address = this->matrix[i][j];
  this->logger->incremet("Write to memory");
  std::string result = this->system->get_memory()->replace(address, value);
}

void Matrix::set(int core_id, unsigned int i, unsigned int j, int value) {
  using namespace std;
  LocalCache* target_cache = this->system->get_local_cache(core_id);
  SharedCache* shared_cache = this->system->get_shared_cache();
  Memory* memory = this->system->get_memory();
  string address = this->matrix[i][j];

  string existed_tag = target_cache->get_tag(address, false);
  string inserted_tag;

  if (existed_tag == "") {
    this->logger->incremet("Write to " + std::to_string(core_id) + " cache");
    inserted_tag = target_cache->insert(value, address);
    
    string tag_in_shared_cache = shared_cache->get_tag(address, true);

    if (tag_in_shared_cache == "") {
      this->logger->incremet("Write to shared cache");
      tag_in_shared_cache = shared_cache->insert(value, address);
    } else {
      this->logger->incremet("Update in shared cache");
      shared_cache->replace(tag_in_shared_cache, value);
    }

    return;
  } else {
    this->logger->incremet("Update in " + std::to_string(core_id) + " cache");
    inserted_tag = existed_tag;
    target_cache->replace(inserted_tag, value);

    string tag_in_shared_cache = shared_cache->get_tag(address, true);

    if (tag_in_shared_cache == "") {
      this->logger->incremet("Write to shared cache");
      tag_in_shared_cache = shared_cache->insert(value, address);
    }
    else {
      this->logger->incremet("Update in shared cache");
      shared_cache->replace(tag_in_shared_cache, value);
    }
  }
}

unsigned int Matrix::get_size() {
  return this->size;
}

unsigned int Matrix::get_number_of_cores() {
  return this->system->get_number_of_cores();
}

std::string transform_number(int number, int length) {
  std::string str_number = std::to_string(number);
  int unshift = length - str_number.size();
  std::string result(unshift, ' ');
  return result + str_number;
}

std::string Matrix::to_string() {
  Memory* memory = this->system->get_memory();
  std::string result = "";
  for (unsigned int i = 0; i < this->size; i++) {
    for (unsigned int j = 0; j < this->size; j++) {
      result += transform_number(memory->read(this->matrix[i][j]), 3)  + " ";
    }
    result += "\n";
  }
  return result;
}

std::string Matrix::to_JSON() {
  Memory* memory = this->system->get_memory();
  std::string result = "";
  for (unsigned int i = 0; i < this->size; i++) {
    result += "[";
    for (unsigned int j = 0; j < this->size; j++) {
      result += std::to_string(memory->read(this->matrix[i][j])) + ", ";
    }
    result = result.substr(0, result.size() - 2);
    result += "],";
  }
  return "[" + result.substr(0, result.size() - 1) + "]";
}

Logger* Matrix::get_logger() {
  return this->logger;
}

System* Matrix::get_system() {
  return this->system;
}
