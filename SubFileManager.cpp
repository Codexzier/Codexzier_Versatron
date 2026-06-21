//
// Created by codexzier on 22.06.26.
//

#include "SubFileManager.h"

#include <SD.h>
// #include <Arduino.h>
#include "FS.h"
// #include "SD.h"
// #include "SPI.h"

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
}

void SubFileManager::init() {
    Serial.println("create instance of the filename list or reset");
    if (!_filenames) {
        Serial.println("set instance of filename list");
        _filenames = std::make_unique<std::vector<std::string>>();
    }

    readSdCard();
}
