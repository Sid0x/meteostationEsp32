#include "Arduino.h"
#include "FS.h"

#ifndef  MeteoFlashUtils_h
#define  MeteoFlashUtils_h

class MeteoFlashUtils {
  public:
    String listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void createDir(fs::FS &fs, const char * path);
    void removeDir(fs::FS &fs, const char * path);
    void readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);
    void deleteFile(fs::FS &fs, const char * path);
    void testFileIO(fs::FS &fs, const char * path);
    void initializationSD(const int flashCardsPin);
    void initializationESP(const bool formatSPIFFSifFailed);
    void prepareDb();
    void deleteDb();
};

#endif

//  listDir(SD/SPIFFS, "/", 0);
//  createDir(SD/SPIFFS, "/mydir");
//  removeDir(SD/SPIFFS, "/mydir");
//  listDir(SD/SPIFFS, "/", 2);
//  writeFile(SD/SPIFFS, "/hello.txt", "Hello ");
//  appendFile(SD/SPIFFS, "/hello.txt", "World!\n");
//  readFile(SD/SPIFFS, "/hello.txt");
//  deleteFile(SD/SPIFFS, "/foo.txt");
//  renameFile(SD/SPIFFS, "/hello.txt", "/foo.txt");
//  readFile(SD/SPIFFS, "/foo.txt");
//  testFileIO(SD/SPIFFS, "/test.txt");
