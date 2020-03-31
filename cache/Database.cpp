#include "Database.h"
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <filesystem>

namespace fs = std::experimental::filesystem;

Database::Database()
{
  std::cout << "Creting db: " << fs::current_path();
}


Database::~Database()
{
}
