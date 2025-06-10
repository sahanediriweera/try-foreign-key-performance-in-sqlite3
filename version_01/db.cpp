#include "lib/db.h"
#include <sqlite3.h>
#include <chrono>
#include <cstdio>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    (void)NotUsed;
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool openDB(const char *filename, sqlite3 **database)
{
    int rc = sqlite3_open(filename, database);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(*database));
        return false;
    }
    printf("Opened database successfully\n");
    return true;
}

bool executeSQL(sqlite3 *db, const char *query, bool useCallback)
{
    char *errMsg = nullptr;
    auto start = std::chrono::high_resolution_clock::now();
    
    int rc = sqlite3_exec(db, query, useCallback ? callback : nullptr, nullptr, &errMsg);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    
    printf("SQL executed successfully in %ld microseconds\n", duration.count());
    return true;
}