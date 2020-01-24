#include "Arduino.h"
#include "FS.h"

#ifndef  FlashUtils_h
#define  FlashUtils_h

class FlashUtils {
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
    void initializationSPIFFS(const bool formatSPIFFSifFailed);
    void prepareDb(fs::FS &fs);
    void deleteDb(fs::FS &fs);
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
