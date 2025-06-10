#include <cstdio>
#include <cstdlib>
#include <sqlite3.h>
#include <chrono>
#include <iostream>
#include "lib/queries.h"
#include "lib/db.h"

void die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    abort();
}

int main(int argc, char **argv)
{
    const char *filename = "db.sqlite3";
    QUERY_t queryType = getQueryType(argc, argv);
    
    if (queryType == NO_QUERY)
    {
        printUsage(argv[0]);
        die("No proper query type specified");
    }
    
    sqlite3 *db = nullptr;
    if (!openDB(filename, &db))
    {
        return EXIT_FAILURE;
    }
    
    const char *sqlQuery = getQuery(queryType);
    bool useCallback = queryNeedsCallback(queryType);    
    if (!executeSQL(db, sqlQuery, useCallback))
    {
        sqlite3_close(db);
        return EXIT_FAILURE;
    }
    
    sqlite3_close(db);
    return EXIT_SUCCESS;
}