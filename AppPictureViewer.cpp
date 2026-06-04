//
// Created by codexzier on 03.06.26.
//

#include "AppPictureViewer.h"


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
