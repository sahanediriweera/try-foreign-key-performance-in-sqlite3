#include <cstdio>
#include <cstdlib>
#include <sqlite3.h>

void die(const char *msg)
{
    fprintf(stderr, "$s\n", msg);
    abort();
}

static int callback(void *Notused, int argc, char **argv, char **azColName)
{
    int i;

    for (i = 0; i < argc; i++)
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
        printf("Failed to open database %s\n", sqlite3_errmsg(*database));
    }

    printf("Opened database successfully \n");

    return true;
}

bool executeSQL(sqlite3 *db, const char *query)
{
    char *errMsg = nullptr;

    int rc = sqlite3_exec(db, query, callback, nullptr, &errMsg);

    if (rc != SQLITE_OK)
    {
        printf("SQL errnor %s\n", errMsg);
        sqlite3_free(errMsg);
        return false;
    }

    printf("SQL executed Successfully\n");

    return true;
}

typedef enum
{
    NO_QUERY = 0,
    CREATE_TABLE = 1,
    INSERT_DATA = 2,
    SELECT_DATA = 3,
} QUERY_t;

const char *getQuery(QUERY_t query)
{
    switch (query)
    {
    case CREATE_TABLE:
        return "CREATE TABLE IF NOT EXISTS STUDENT (ID INTEGER PRIMARY KEY NOT NULL, FIRST_NAME TEXT NOT NULL, LAST_NAME TEXT NOT NULL, EMAIL TEXT NOT NULL);";

    case INSERT_DATA:
        return "INSERT INTO STUDENT (FIRST_NAME, LAST_NAME, EMAIL) VALUES ('John', 'Doe', 'john@example.com');";

    case SELECT_DATA:
        return "SELECT * FROM STUDENT;";

    default:
        return "";
    }
}

QUERY_t getQueryType(int argv, char **argc)
{
    switch (atoi(argc[1]))
    {
    case 1:
        return CREATE_TABLE;
    case 2:
        return INSERT_DATA;
    case 3:
        return SELECT_DATA;
    }

    return NO_QUERY;
}

int main(int argv, char **argc)
{
    const char *filename = "db.sqlite3";

    QUERY_t queryType = getQueryType(argv, argc);

    if (queryType == NO_QUERY)
    {
        die("No propert query type");
    }

    sqlite3 *db = nullptr;

    if (!openDB(filename, &db))
    {
        return EXIT_FAILURE;
    }

    const char *createTableSql = getQuery(queryType);

    if (!executeSQL(db, createTableSql))
    {
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    sqlite3_close(db);
    return EXIT_SUCCESS;
}