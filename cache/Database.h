#include <stdio.h>
#include <sqlite3.h>
#include "Matrix.h"
#include "Logger.h"

#pragma once

class Database {
public:
	Database();
	~Database();
  void insert(Matrix* matrix, bool processed);
  void insert(Logger* logger);
private:
  sqlite3* database;
  std::string session;
};

