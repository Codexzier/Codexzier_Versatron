//
// Created by codexzier on 22.05.26.
//

#include "AppTorchRun.h"

void AppTorchRun::setBackground() {

    if (_color == _colorBackground) {
        return;
    }

    _colorBackground = _color;
    _tft->fillScreen(_colorBackground);
}

void AppTorchRun::drawUpdate() {

    switch (_mode) {
        case 1: {
            setBackground();
            break;
        }
        case 2: {

            break;
        }
        case 3: {

            break;
        }
    }

}

void AppTorchRun::reset() {
    _option = 1;
    _canBeClosed = false;
}

bool AppTorchRun::CanBeClosed() {
    _canBeClosed = true;
}

void AppTorchRun::setValue1(int16_t value) {
    _brightness = value;
}

void AppTorchRun::setButton1() {

    switch (_option) {
        case 1: {
            _color = _tft->C_WHITE;
            _option++;
            break;
        }
        case 2: {
            _tft->fillScreen(_tft->C_RED);
            _color = _tft->C_WHITE;
            _option++;
            break;
        }
        case 3: {
            _tft->fillScreen(_tft->C_BLUE);
            _option = 1;
            break;
        }
    }
}

void AppTorchRun::setButton2() {

    if (_mode >= 3) {
        _mode = 0;
    }
    else {
        _mode++;
    }

}

void AppTorchRun::setButton3() {
    _canBeClosed = true;
}
