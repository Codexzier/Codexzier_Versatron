//
// Created by codexzier on 21.06.26.
//

#include "AppRadioRadar.h"

void AppRadioRadar::drawUpdate() {

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

void AppRadioRadar::setButton1() {

}

void AppRadioRadar::setButton2() {

}

void AppRadioRadar::reset() {
    _hasDraw = false;
}