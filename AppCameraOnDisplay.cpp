//
// Created by codexzier on 23.06.26.
//

#include "AppCameraOnDisplay.h"


void AppCameraOnDisplay::drawPicture(const uint8_t *bitmap) {

}

void AppCameraOnDisplay::drawUpdate() {

    if (!_hasDraw) {
        return;
    }

    _hasDraw = true;
}
