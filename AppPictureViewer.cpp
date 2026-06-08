//
// Created by codexzier on 03.06.26.
//

#include "AppPictureViewer.h"
// #include <Arduino.h>
// #include "FS.h"
// #include "SD.h"
// #include "SPI.h"


void AppPictureViewer::initExtend() {

    // _tft->setCursor(60, 60);
    // _tft->print("Start SD Card reader");
    //
    // _tft->setCursor(60, 80);
    // if (!SD.begin()) {
    //     _tft->print("Card Mount Failed");
    //     return;
    // }
    //
    // uint8_t cardType = SD.cardType();
    //
    // _tft->setCursor(6, 100);
    // if (cardType == CARD_NONE) {
    //     _tft->print("No SD card attached");
    //     return;
    // }
    //
    // _tft->print("SD Card Type: ");
    // if (cardType == CARD_MMC) {
    //     _tft->print("MMC");
    // } else if (cardType == CARD_SD) {
    //     _tft->print("SDSC");
    // } else if (cardType == CARD_SDHC) {
    //     _tft->print("SDHC");
    // } else {
    //     _tft->print("UNKNOWN");
    // }
}

void AppPictureViewer::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    _tft->drawCircle(120, 120, 100, _colorOff);
    _tft->drawCircle(120, 120, 70, _colorOff);
    _tft->drawCircle(120, 120, 40, _colorOff);
    _tft->drawCircle(120, 120, 10, _colorOff);

    _tft->drawFastVLine(120, 0, 240, _colorOff);
    _tft->drawFastHLine(0, 120, 240, _colorOff);

    _hasDraw = true;
}

void AppPictureViewer::setButton1() {

}

void AppPictureViewer::setButton2() {

}
