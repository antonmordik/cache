#include "Memory.h"

Memory::Memory()
{
  this->lines = nullptr;
}


Memory::~Memory()
{
  delete this->lines;
}

CacheLine* findNodeByTag(LineNode* &node, std::string tag) {
  if (!!node) {
    if (node->data && node->data->tag == tag) {
      return node->data;
    } else {
      return findNodeByTag(node->next, tag);
    }
  }
}

void fillNode(LineNode* &node, CacheLine* value) {
  if (node == nullptr) {
    node = new LineNode();
    node->next = nullptr;
    node->data = value;
    return;
  } else {
    fillNode(node->next, value);
  }
}

CacheLine* Memory::getLine(std::string tag) {
  if (!this->lines) {
    return nullptr;
  }
  else {
    return findNodeByTag(this->lines, tag);
  }
}

void Memory::putLine(std::string tag, std::string data) {
  CacheLine* insert = new CacheLine(tag, data);
  fillNode(this->lines, insert);
}
