#include "Database.h"
#include "Caches.h"
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <filesystem>

namespace fs = std::experimental::filesystem;

Database::Database() {
  using namespace std;
  this->session = to_string(get_now_in_milliseconds());
  string dbFilePath = fs::current_path().u8string() + "\\storage.db";
  cout << "Using db: " << dbFilePath << std::endl;
  int exec_code = sqlite3_open(dbFilePath.c_str(), &this->database);
  if (exec_code) {
    cout << "\nUnable to open database. Exited with code " << exec_code << endl;
  }
  string create_statistics = "CREATE TABLE IF NOT EXISTS statistics("  \
    "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE," \
    "timestamp BLOB NOT NULL," \
    "json BLOB NOT NULL);";

  const char* c_create_statistics = create_statistics.c_str();
  exec_code = sqlite3_exec(this->database, c_create_statistics, NULL, 0, NULL);
  if (exec_code != SQLITE_OK) {
    cout << "\nUnable to execute sql query. Exited with core " << exec_code << endl;
  }

  string create_matrix = "CREATE TABLE IF NOT EXISTS matrix("  \
    "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE," \
    "timestamp BLOB NOT NULL," \
    "matrix BLOB NOT NULL," \
    "processed INTEGER DEFAULT 0);";

  const char* c_create_matrix = create_matrix.c_str();
  exec_code = sqlite3_exec(this->database, c_create_matrix, NULL, 0, NULL);
  if (exec_code != SQLITE_OK) {
    cout << "\nUnable to execute sql query. Exited with code " << exec_code << endl;
  }
}



Database::~Database() {
  sqlite3_close(this->database);
}

void Database::insert(Matrix* matrix, bool processed) {
  using namespace std;
  string insert_query = "INSERT INTO matrix (timestamp, matrix, processed) VALUES " \
    "('" + this->session + "', '" + matrix->to_JSON() + "', " + to_string((int)processed) + ");";
  const char* c_insert_matrix = insert_query.c_str();
  int exec_code = sqlite3_exec(this->database, c_insert_matrix, NULL, 0, NULL);
  if (exec_code != SQLITE_OK) {
    cout << "\nUnable to execute sql query. Exited with code " << exec_code << endl;
  }
}

void Database::insert(Logger* logger) {
  using namespace std;
  string insert_query = "INSERT INTO statistics (timestamp, json) VALUES " \
    "('" + this->session + "', '" + logger->to_JSON() + "');";
  const char* c_insert_statistics = insert_query.c_str();
  int exec_code = sqlite3_exec(this->database, c_insert_statistics, NULL, 0, NULL);
  if (exec_code != SQLITE_OK) {
    cout << "\nUnable to execute sql query. Exited with code " << exec_code << endl;
  }
}
