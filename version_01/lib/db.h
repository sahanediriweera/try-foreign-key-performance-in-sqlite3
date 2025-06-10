#ifndef DB_H
#define DB_H

#include <sqlite3.h>

bool openDB(const char *filename, sqlite3 **database);
bool executeSQL(sqlite3 *db, const char *query, bool useCallback = false);

#endif