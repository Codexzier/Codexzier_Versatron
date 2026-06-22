//
// Created by codexzier on 03.06.26.
//

#include "AppPictureViewer.h"


void AppPictureViewer::initExtend() {

    _applicationName = "Picture Viewer";

}

void AppPictureViewer::drawPicture() {

    Serial.println("Read file");

    _tft->drawRoundRect(80, 90, 80, 30, 4, _colorOn);
    _tft->setCursor(90, 100);
    _tft->setFont(FontDefault);
    _tft->print("Read from file: ");
    _tft->writeBuffer();
    const uint8_t* bitmap = _fileManager->GetPictureData(_pictureIndex);

    if (bitmap == nullptr) {
        return;
    }

    // draw recorded picture
    const uint8_t* bitmapIter = bitmap;
    uint16_t colour;
    for (int16_t y = 239; y >= 0; y--) {

        for (int16_t x = 0; x < 240; x++) {

            uint8_t hi = pgm_read_byte(bitmapIter);       // high byte
            uint8_t lo = pgm_read_byte(bitmapIter + 1);   // low byte
            colour = (static_cast<uint16_t>(hi) << 8) | static_cast<uint16_t>(lo);
            bitmapIter += 2;

            _tft->drawPixel(x, y, colour);
        }
    }
    _tft->writeBuffer();
}



void AppPictureViewer::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    _tft->setCursor(120, 120);

    drawPicture();

    _tft->drawCircle(120, 120, 119, _colorOn);

    _hasDraw = true;
}

void AppPictureViewer::setButton1() {

    if (_pictureCount == 0) {
        _pictureCount = _fileManager->GetCountPictures();
    }

    if (_pictureIndex < _pictureCount - 1) {
        _pictureIndex++;
    }
    else {
        _pictureIndex = 0;
    }

    _hasDraw = false;
}

void AppPictureViewer::setButton2() {

}

void AppPictureViewer::reset() {
    _hasDraw = false;
}
