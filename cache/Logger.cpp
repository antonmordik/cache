#include "Logger.h"

void Logger::incremet(std::string key) {
  if (this->stats.find(key) != this->stats.end()) {
    this->stats.at(key)++;
  } else {
    this->stats.insert(std::pair<std::string, int>(key, 1));
  }
}

std::string Logger::get_statistics() {
  using namespace std;
  string result = "";
  for (auto const& key : this->stats) {
    result.append("" + key.first + ": " + to_string(key.second) + " time(s)\n");
  }
  return result;
}

std::string Logger::to_JSON() {
  using namespace std;
  string output = "", result = "";
  for (auto const& key : this->stats) {
    output += "\"" + key.first + "\":" + to_string(key.second) + ", ";
  }
  result = output.substr(0, output.size() - 2);
  return "{" + result + "}";
}
