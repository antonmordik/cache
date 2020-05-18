#include <string>
#include <map>
#pragma once

std::string to_hex_string(unsigned int number);

class Memory {
private:
  std::map<std::string, int> lines;
public:
  Memory();
  ~Memory();
  std::string insert(int data);
  int clear(std::string address);
  std::string replace(std::string address, int data);
  int read(std::string address);
  std::string to_string();
};
