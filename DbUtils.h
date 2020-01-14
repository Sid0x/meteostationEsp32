#ifndef  DbUtils_h
#define  DbUtils_h
#endif

#include "sqlite3.h"

class DbUtils {
  public:
    static int openDb(const char *filename, sqlite3 **db);
    static int dbExec(sqlite3 *db, const char *sql);
    static void checkDb();
  private:
    static int callBack(void *data, int argc, char **argv, char **azColName);
};
