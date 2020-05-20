#include <map>
#include <string>
#pragma once

class Logger {
private:
  std::map<std::string, int> stats;
public:
  void incremet(std::string key);
  std::string get_statistics();
  std::string to_JSON();
};

