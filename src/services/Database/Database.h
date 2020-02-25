#include <sqlite3.h>

#ifndef CACHE_DATABASE_H
#define CACHE_DATABASE_H

class Database {
  private:
    sqlite3 *db;
  public:
    void put();
};


#endif
