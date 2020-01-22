#include "MeteoDbUtils.h"

#include "stdio.h"
#include "stdlib.h"
#include "sqlite3.h"
#include "FS.h"

const char* data = "Callback function called";
char *zErrMsg = 0;

int MeteoDbUtils::callBack(void *data, int argc, char **argv, char **azColName) {
  int i;
  Serial.printf("%s: ", (const char*)data);
  for (i = 0; i < argc; i++) {
    Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  Serial.printf("\n");
  return 0;
}

int MeteoDbUtils::openDb(const char *filename, sqlite3 **db) {
  int rc = sqlite3_open(filename, db);
  if (rc) {
    Serial.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
    return rc;
  } else {
    Serial.printf("Opened database successfully\n");
  }
  return rc;
}

int MeteoDbUtils::dbExec(sqlite3 *db, const char *sql) {
  Serial.println(sql);
  long start = micros();
  int rc = sqlite3_exec(db, sql, callBack, (void*)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    Serial.printf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    Serial.printf("Operation done successfully\n");
  }
  Serial.print(F("Time taken:"));
  Serial.println(micros() - start);
  return rc;
}

void MeteoDbUtils::checkDb() {
  sqlite3 *db;

  sqlite3_initialize();
  int rc;

  if (openDb("/sd/db/esp32.db", &db))
    return;

  char* sql = "CREATE TABLE IF NOT EXISTS Data("
              "id             INT     PRIMARY KEY NOT NULL,"
              "timestamp      TEXT    NOT NULL,"
              "statusws16     TEXT    NOT NULL,"
              "temperature    TEXT    NOT NULL,"
              "humidity       TEXT,"
              "pressure       TEXT,"
              "mhZ19          TEXT,"
              "co2            TEXT );";

  rc = dbExec(db, sql);
  if (rc != SQLITE_OK) {
    sqlite3_close(db);
    return;
  }
}
