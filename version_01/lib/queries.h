#ifndef QUERIES_H
#define QUERIES_H

typedef enum
{
    NO_QUERY = 0,
    CREATE_TABLE_NO_FK = 1,
    CREATE_TABLE_WITH_FK = 2,
    INSERT_STUDENT_DATA = 3,
    INSERT_SUBJECT_DATA = 4,
    INSERT_BULK_STUDENTS = 5,
    INSERT_BULK_SUBJECTS = 6,
    SELECT_STUDENTS = 7,
    SELECT_SUBJECTS = 8,
    SELECT_WITH_JOIN = 9,
    CREATE_INDEX = 10,
    PERFORMANCE_TEST = 11,
} QUERY_t;

const char *getQuery(QUERY_t query);
QUERY_t getQueryType(int argc, char **argv);
void printUsage(const char *progName);
bool queryNeedsCallback(QUERY_t queryType);

#endif