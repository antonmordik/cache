#include "Memory.h"
#include <math.h>

std::string to_hex_string(int num)
{
  std::string B[16] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F" };
  std::string answer = "";
  int A[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
  int num2;
  int ssc[4];
  for (int i = 0; i < 4; i++) {
    num2 = num / 16;
    ssc[i] = num - (num2 * 16);
    num = num2;
  }
  for (int j = 3; j >= 0; j--) {
    for (int k = 0; k < 16; k++) {
      if (ssc[j] == A[k]) {
        answer += B[k];
      }
    }
  }
  return answer;
}

Memory::Memory() {
  for (int address = 0; address < pow(16, 4); address++) {
    this->lines.insert(std::pair<std::string, int>(to_hex_string(address), -1));
  }
};

std::string Memory::insert(int data) {
  for (int address = 0; address < pow(16, 4); address++) {
    if (this->lines.at(to_hex_string(address)) == -1) {
      this->lines.at(to_hex_string(address)) = data;
      return to_hex_string(address);
    }
  }
  return "";
}

std::string Memory::replace(std::string address, int data) {
  this->lines.at(address) = data;
  return address;
}

int Memory::read(std::string address) {
  return this->lines.at(address);
}

std::string Memory::to_string() {
  std::string result = "";
  for (int address = 0; address < pow(16, 2); address++) {
    result += "[" + to_hex_string(address) + "] - " + std::to_string(this->lines.at(to_hex_string(address)))  + "\n";
  }
	return result;
}

int Memory::clear(std::string address) {
  int old_data = this->lines.at(address);
  this->lines.at(address) = -1;
  return old_data;
}

Memory::~Memory() {
  this->lines.clear();
}
