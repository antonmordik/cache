#pragma once
#include <stdio.h>
#include <sqlite3.h>

class Database
{
public:
	Database();
	~Database();
private:
  sqlite3* database;
};

