#include "lib/queries.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>


bool queryNeedsCallback(QUERY_t queryType)
{
    return (queryType == SELECT_STUDENTS || 
            queryType == SELECT_SUBJECTS || 
            queryType == SELECT_WITH_JOIN);
}

const char *getQuery(QUERY_t query)
{
    switch (query)
    {
    case CREATE_TABLE_NO_FK:
        return "CREATE TABLE IF NOT EXISTS STUDENT ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "FIRST_NAME TEXT NOT NULL, "
               "LAST_NAME TEXT NOT NULL, "
               "EMAIL TEXT NOT NULL UNIQUE); "
               
               "CREATE TABLE IF NOT EXISTS SUBJECT ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "SUBJECT_NAME TEXT NOT NULL, "
               "SUBJECT_CODE TEXT NOT NULL UNIQUE, "
               "CREDITS INTEGER NOT NULL, "
               "STUDENT_ID INTEGER);";
               
    case CREATE_TABLE_WITH_FK:
        return "PRAGMA foreign_keys = ON; "
               "CREATE TABLE IF NOT EXISTS STUDENT ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "FIRST_NAME TEXT NOT NULL, "
               "LAST_NAME TEXT NOT NULL, "
               "EMAIL TEXT NOT NULL UNIQUE); "
               
               "CREATE TABLE IF NOT EXISTS SUBJECT ("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "SUBJECT_NAME TEXT NOT NULL, "
               "SUBJECT_CODE TEXT NOT NULL UNIQUE, "
               "CREDITS INTEGER NOT NULL, "
               "STUDENT_ID INTEGER, "
               "FOREIGN KEY (STUDENT_ID) REFERENCES STUDENT(ID) ON DELETE CASCADE);";
               
    case INSERT_STUDENT_DATA:
        return "INSERT INTO STUDENT (FIRST_NAME, LAST_NAME, EMAIL) "
               "VALUES ('Vanessa', 'Kirby', 'vanessa@kirby.com');";
               
    case INSERT_SUBJECT_DATA:
        return "INSERT INTO SUBJECT (SUBJECT_NAME, SUBJECT_CODE, CREDITS, STUDENT_ID) "
               "VALUES ('Computer Science', 'CS101', 3, 1);";
               
    case INSERT_BULK_STUDENTS:
        return "BEGIN TRANSACTION; "
               "INSERT INTO STUDENT (FIRST_NAME, LAST_NAME, EMAIL) VALUES "
               "('Alice', 'Smith', 'alice@example.com'), "
               "('Bob', 'Johnson', 'bob@example.com'), "
               "('Charlie', 'Brown', 'charlie@example.com'), "
               "('David', 'Wilson', 'david@example.com'), "
               "('Eve', 'Davis', 'eve@example.com'), "
               "('Frank', 'Miller', 'frank@example.com'), "
               "('Grace', 'Taylor', 'grace@example.com'), "
               "('Henry', 'Anderson', 'henry@example.com'), "
               "('Ivy', 'Thomas', 'ivy@example.com'), "
               "('Jack', 'Jackson', 'jack@example.com'); "
               "COMMIT;";
               
    case INSERT_BULK_SUBJECTS:
        return "BEGIN TRANSACTION; "
               "INSERT INTO SUBJECT (SUBJECT_NAME, SUBJECT_CODE, CREDITS, STUDENT_ID) VALUES "
               "('Mathematics', 'MATH101', 4, 1), "
               "('Physics', 'PHYS101', 3, 1), "
               "('Chemistry', 'CHEM101', 3, 2), "
               "('Biology', 'BIO101', 4, 2), "
               "('English Literature', 'ENG101', 3, 3), "
               "('History', 'HIST101', 3, 3), "
               "('Computer Science', 'CS101', 4, 4), "
               "('Statistics', 'STAT101', 3, 4), "
               "('Psychology', 'PSY101', 3, 5), "
               "('Economics', 'ECON101', 4, 5), "
               "('Art History', 'ART101', 2, 6), "
               "('Music Theory', 'MUS101', 2, 6), "
               "('Philosophy', 'PHIL101', 3, 7), "
               "('Sociology', 'SOC101', 3, 7), "
               "('Political Science', 'POLI101', 3, 8), "
               "('Geography', 'GEO101', 3, 8), "
               "('Calculus', 'MATH201', 4, 9), "
               "('Data Structures', 'CS201', 4, 9), "
               "('Organic Chemistry', 'CHEM201', 4, 10), "
               "('Linear Algebra', 'MATH301', 3, 10); "
               "COMMIT;";
               
    case SELECT_STUDENTS:
        return "SELECT * FROM STUDENT ORDER BY ID;";
        
    case SELECT_SUBJECTS:
        return "SELECT * FROM SUBJECT ORDER BY ID;";
        
    case SELECT_WITH_JOIN:
        return "SELECT "
               "s.ID as student_id, "
               "s.FIRST_NAME, "
               "s.LAST_NAME, "
               "s.EMAIL, "
               "sub.ID as subject_id, "
               "sub.SUBJECT_NAME, "
               "sub.SUBJECT_CODE, "
               "sub.CREDITS "
               "FROM STUDENT s "
               "LEFT JOIN SUBJECT sub ON s.ID = sub.STUDENT_ID "
               "ORDER BY s.ID, sub.ID;";
               
    case CREATE_INDEX:
        return "CREATE INDEX IF NOT EXISTS idx_student_email ON STUDENT(EMAIL); "
               "CREATE INDEX IF NOT EXISTS idx_subject_code ON SUBJECT(SUBJECT_CODE); "
               "CREATE INDEX IF NOT EXISTS idx_subject_student_id ON SUBJECT(STUDENT_ID);";
               
    case PERFORMANCE_TEST:
        return "PRAGMA journal_mode=WAL; "
               "PRAGMA synchronous=NORMAL; "
               "PRAGMA cache_size=10000; "
               "PRAGMA temp_store=MEMORY; "
               "PRAGMA foreign_keys=ON;";
               
    default:
        return "";
    }
}

QUERY_t getQueryType(int argc, char **argv)
{
    if (argc < 2)
        return NO_QUERY;
    switch (atoi(argv[1]))
    {
    case 1:
        return CREATE_TABLE_NO_FK;
    case 2:
        return CREATE_TABLE_WITH_FK;
    case 3:
        return INSERT_STUDENT_DATA;
    case 4:
        return INSERT_SUBJECT_DATA;
    case 5:
        return INSERT_BULK_STUDENTS;
    case 6:
        return INSERT_BULK_SUBJECTS;
    case 7:
        return SELECT_STUDENTS;
    case 8:
        return SELECT_SUBJECTS;
    case 9:
        return SELECT_WITH_JOIN;
    case 10:
        return CREATE_INDEX;
    case 11:
        return PERFORMANCE_TEST;
    default:
        return NO_QUERY;
    }
}

void printUsage(const char *progName)
{
    printf("Usage: %s <option>\n", progName);
    printf("Options:\n");
    printf("  1 - Create tables (NO foreign key constraints)\n");
    printf("  2 - Create tables (WITH foreign key constraints)\n");
    printf("  3 - Insert single student record\n");
    printf("  4 - Insert single subject record\n");
    printf("  5 - Insert bulk student records (with transaction)\n");
    printf("  6 - Insert bulk subject records (with transaction)\n");
    printf("  7 - Select all students\n");
    printf("  8 - Select all subjects\n");
    printf("  9 - Select with JOIN (students and their subjects)\n");
    printf("  10 - Create indexes\n");
    printf("  11 - Apply performance optimizations\n");
    printf("\nRecommended workflow:\n");
    printf("1. Run option 1 or 2 to create tables\n");
    printf("2. Run option 5 to insert students\n");
    printf("3. Run option 6 to insert subjects\n");
    printf("4. Run option 9 to see joined data\n");
    printf("5. Run option 10 to create indexes\n");
    printf("6. Compare performance with option 11\n");
}