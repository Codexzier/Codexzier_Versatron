//
// Created by codexzier on 03.06.26.
//

#include "AppPictureViewer.h"




void AppPictureViewer::initExtend() {

    _applicationName = "Picture Viewer";

    // read pictures
    // File root = SD.open("/");
    // if (!root) {
    //     Serial.println("Failed to open directory");
    //     delay(1000);
    //     return;
    // }
    //
    // Serial.println("Check directory");
    // if (!root.isDirectory()) {
    //     Serial.println("Not a directory");
    //     delay(1000);
    //     return;
    // }
    //

    // else {
    //     Serial.println("reset list");
    //     _filenames->clear();
    // }
    //
    // Serial.println("read root directory");
    // File file = root.openNextFile();
    // while (file) {
    //     if (file.isDirectory()) {
    //         Serial.print("  DIR : ");
    //         Serial.println(file.name());
    //     } else {
    //
    //         std::string filename = file.name();
    //         Serial.print("  FILE: ");
    //         Serial.print(filename.c_str());
    //         Serial.print("  SIZE: ");
    //         Serial.println(file.size());
    //
    //         _filenames->push_back(filename);
    //     }
    //     file = root.openNextFile();
    // }
    // file.close();

    //delay(4000);
}

void AppPictureViewer::drawPicture() {
    /*
    const std::string fullpath = (*_filenames)[_viewIndex];
    Serial.print("try to read ");
    File file = SD.open(fullpath.c_str());
    if(!file){
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to open");
        _tft->setCursor(60, 60 + 20);
        _tft->print("file for reading");
        Serial.println("Failed to open file for reading");
        delay(1000);
        return;
    }

    _tft->print("Read from file: ");
    Serial.print("Read from file: ");
    _tft->writeBuffer();

    for (int16_t y = 239; y >= 0; y--) {

        if (!file.available()) {
            continue;
        }

        for (int16_t x = 0; x < 240; x++) {

            //const uint16_t pixelFarbe = GetNextPixelColorValue(file);

            //_tft->drawPixel(x, y, pixelFarbe);
        }
    }
    file.close();
    _tft->writeBuffer();
    */
}



void AppPictureViewer::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    //drawPicture();
    _tft->setCursor(120, 120);
    _tft->drawCircle(120, 120, 30, _colorOn);

    _hasDraw = true;
}

void AppPictureViewer::setButton1() {

    /*
    if (_viewIndex < static_cast<int>(_filenames->size())) {
        _viewIndex++;
    }
    */

    _hasDraw = false;
}

void AppPictureViewer::setButton2() {

}

void AppPictureViewer::reset() {
    _hasDraw = false;
}
