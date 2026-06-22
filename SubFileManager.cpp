//
// Created by codexzier on 22.06.26.
//

#include "SubFileManager.h"

#include <SD.h>
#include <Arduino.h>
#include "FS.h"

uint16_t SubFileManager::GetNextPixelColorValue(File &file) {


    const uint8_t highByte = file.read(); // Zweites Byte (hochwertig)
    const uint8_t lowByte = file.read();  // Erstes Byte (niederwertig)

    const uint16_t color = highByte << 8 | lowByte;

    return color;
}

void SubFileManager::readSdCard() {

     if (!SD.begin(21)) {
         Serial.print("Card Mount Failed");
         delay(1000);
         return;
    }

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
         Serial.print("No SD card attached");
         return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
         Serial.print("MMC");
    } else if (cardType == CARD_SD) {
         Serial.print("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.print("SDHC");
    } else {
        Serial.print("UNKNOWN");
    }

    _sdSuccess = true;
}

void SubFileManager::init() {
    Serial.println("create instance of the filename list or reset");
    if (!_filenames) {
        Serial.println("set instance of filename list");
        _filenames = std::make_unique<std::vector<std::string>>();
    }

    readSdCard();
}

// SD card write file
void SubFileManager::writeFile(const char * path, uint8_t * data, size_t len){

    Serial.printf("Writing file: %s\n", path);

    File file = SD.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        delay(1000);
        return;
    }

    if(file.write(data, len) == len){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
        delay(1000);
    }
    file.close();
}

void SubFileManager::readFiles() {

    Serial.println("Get root");
    File root = SD.open("/");
    if (!root) {
        Serial.println("Failed to open directory");
        delay(1000);
        return;
    }

    Serial.println("Check directory");
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        delay(1000);
        return;
    }

    Serial.println("create instance of the filename list or reset");
    if (!_filenames) {
        Serial.println("set instance of filename list");
        _filenames = std::make_unique<std::vector<std::string>>();
    }
    else {
        Serial.println("reset list");
        _filenames->clear();
    }

    Serial.println("read root directory");
    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
        } else {

            std::string filename = file.name();
            Serial.print("  FILE: ");
            Serial.print(filename.c_str());
            Serial.print("  SIZE: ");
            Serial.println(file.size());

            _filenames->push_back(filename);
        }
        file = root.openNextFile();
    }
    file.close();

    const int countFiles = static_cast<int>(_filenames->size());
    Serial.print("Count files: "); Serial.println(countFiles, DEC);
}

int SubFileManager::GetCountPictures() {
    
    readFiles();

    return static_cast<int>(_filenames->size());
}

int SubFileManager::GetCardSizeMb() {
    return SD.usedBytes() / 1024 / 1024;
}

uint8_t* SubFileManager::GetPictureData(int index) {

    //if (!_filenames) {
        Serial.println("Files are not readed! try to read");
        readFiles();

        if (!_filenames) {
            return  nullptr;
        }
    //}
    Serial.println("Read file from index.");
    const std::string filename = "/" + (*_filenames)[index];

    Serial.print("Read file: ");  Serial.println(filename.c_str());
    File file = SD.open(filename.c_str());
    if (!file) {
        Serial.println("File picture can not loaded.");
        return nullptr;
    }

    size_t fileSize = file.size();
    uint8_t* bitmap = new uint8_t[fileSize];
    file.read(bitmap, fileSize);
    file.close();

    return bitmap;
}

bool SubFileManager::IsSdCardInit() {
    return _sdSuccess;
}
