#include <string>
#include <map>
#pragma once

std::string to_hex_string(int num);

class Memory {
private:
  std::map<std::string, std::string> lines;
public:
  Memory();
  ~Memory();
  std::string insert(std::string data);
  std::string clear(std::string address);
  std::string replace(std::string address, std::string data);
  std::string read(std::string address);
};
