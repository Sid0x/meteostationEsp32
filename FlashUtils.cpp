#include "FlashUtils.h"

#include "SPIFFS.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Arduino.h"
#include "WiFi.h"
#include "ArduinoJson.h"

String FlashUtils::listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  String json;
  DynamicJsonDocument doc(2048);
  JsonArray data = doc.createNestedArray("listDir");

  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    data.add("Failed to open directory");
    serializeJson(doc, json);
    return json;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    data.add("Not a directory");
    serializeJson(doc, json);
    return json;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      data.add(String(file.name()));
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
      data.add(String(file.name()));
    }
    file = root.openNextFile();
  }

  serializeJson(doc, json);
  return json;
}

void FlashUtils::createDir(fs::FS &fs, const char * path) {
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void FlashUtils::removeDir(fs::FS &fs, const char * path) {
  Serial.printf("Removing Dir: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void FlashUtils::readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void FlashUtils::writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void FlashUtils::appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void FlashUtils::renameFile(fs::FS &fs, const char * path1, const char * path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void FlashUtils::deleteFile(fs::FS &fs, const char * path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void FlashUtils::testFileIO(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}

void FlashUtils::initializationSD(int flashCardsPin) {

  if (!SD.begin(flashCardsPin)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void FlashUtils::initializationESP(bool formatSPIFFSifFailed) {
  if (!SPIFFS.begin(formatSPIFFSifFailed)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
}

void FlashUtils::prepareDb() {
  String ls = FlashUtils::listDir(SD, "/", 0);
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, ls);
  JsonArray dirs = doc["listDir"];
  bool checkerDir = false;
  bool checkerDb = false;

  for (String dir : dirs) {
    if (dir.equals("/db")) {
      checkerDir = true;
    }
  }

  if (!checkerDir) {
    FlashUtils::createDir(SD, "/db");
  }

  ls = FlashUtils::listDir(SD, "/db", 0);
  deserializeJson(doc, ls);
  dirs = doc["listDir"];
  for (String dir : dirs) {
    if (dir.equals("/db/esp32.db")) {
      checkerDb = true;
    }
  }

  if (!checkerDb) {
    FlashUtils::writeFile(SD, "/db/esp32.db", "");
  }
}

void FlashUtils::deleteDb() {
  deleteFile(SD, "/db/esp32.db");
  removeDir(SD, "/db");
}
