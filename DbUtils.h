#include "sqlite3.h"

#ifndef  DbUtils_h
#define  DbUtils_h

class DbUtils {
  public:
    int openDb(const char *filename, sqlite3 **db);
    int dbExec(sqlite3 *db, const char *sql);
    void checkDb();
  private:
    static int callBack(void *data, int argc, char **argv, char **azColName);
};

#endif
