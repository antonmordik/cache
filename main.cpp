#include "src/utils/Log/Log.cpp"
#include "src/services/Database/Database.cpp"

int main() {
  Log::console("Hello world");
  Database database;
  database.put();
  return 0;
}
