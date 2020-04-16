#include "Database.h"
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <filesystem>

namespace fs = std::experimental::filesystem;

Database::Database()
{
  std::string dbFilePath = fs::current_path().u8string() + "\\storage.db";
  std::cout << "Using db: " << dbFilePath << std::endl;
  int execCode = sqlite3_open(dbFilePath.c_str(), &this->database);
  if (execCode) {
    std::cout << "Unable to open database. Exited with code " << execCode;
  }
}


Database::~Database()
{
  sqlite3_close(this->database);
}
