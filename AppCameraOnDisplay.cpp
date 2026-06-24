//
// Created by codexzier on 23.06.26.
//

#include "AppCameraOnDisplay.h"


void AppCameraOnDisplay::drawPicture(const uint8_t *bitmap) {

}

void AppCameraOnDisplay::drawUpdate() {

    const CameraRecordResult record = _cameraManager->getPictureFast();

    // draw recorded picture
    const uint8_t* bitmapIter = record.Buffer;
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

    if (!_hasDraw) {
        return;
    }

    _hasDraw = true;
}
