#include <string>
#pragma once

enum CacheLineFlag {
  DEFAULT = 0, DITRY = 1
};

struct CacheLine
{
  std::string tag;
  std::string data;
  CacheLineFlag flag;
  int count;

  CacheLine(std::string tag, std::string data) {
    this->tag = tag;
    this->data = data;
    this->flag = CacheLineFlag::DEFAULT;
    this->count = 0;
  }

  CacheLine() {
    this->count = 0;
    this->flag = CacheLineFlag::DEFAULT;
  }
};

struct LineNode {
  CacheLine* data;
  LineNode* next;
};


class Memory
{
public:
	Memory();
	~Memory();
  CacheLine* getLine(std::string tag);
  void putLine(std::string tag, std::string data);
private:
  LineNode *lines;
};

