#ifndef  MeteoFlashUtils_h
#define  MeteoFlashUtils_h
#endif

#include "Arduino.h"
#include "FS.h"

class MeteoFlashUtils {
  public:
    static String listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    static void createDir(fs::FS &fs, const char * path);
    static void removeDir(fs::FS &fs, const char * path);
    static void readFile(fs::FS &fs, const char * path);
    static void writeFile(fs::FS &fs, const char * path, const char * message);
    static void appendFile(fs::FS &fs, const char * path, const char * message);
    static void renameFile(fs::FS &fs, const char * path1, const char * path2);
    static void deleteFile(fs::FS &fs, const char * path);
    static void testFileIO(fs::FS &fs, const char * path);
    static void initializationSD(const int flashCardsPin);
    static void initializationESP(const bool formatSPIFFSifFailed);
    static void prepareDb();
    static void deleteDb();
};

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
