//
// Created by codexzier on 22.05.26.
//

#include "AppTorchRun.h"
#include <string>
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"

void AppTorchRun::setBackground() {

    if (_colorTarget == _colorBackground) {
        return;
    }

    _colorBackground = _colorTarget;
    _tft->fillScreen(_colorBackground);
}

bool AppTorchRun::animationRun(int animationEndCount) {
    if (_modeAnimation1 < animationEndCount) {
        _modeAnimation1++;

        return false;
    }

    _modeAnimation1 = 0;
    return true;
}

void AppTorchRun::setCircleAnimation() {
    _tft->drawCircle(120, 120, _modeAnimation1, _colorCircle);

    if (animationRun(120)) {
        if (_colorCircle == _colorTarget) {
            _colorCircle = _tft->C_BLACK;
        }
        else {
            _colorCircle = _colorTarget;
        }
    }
}

void AppTorchRun::drawUpdate() {

    switch (_mode) {
        case 1: {
            setBackground();
            break;
        }
        case 2: {
            setCircleAnimation();
            break;
        }
        case 3: {

            if (animationRun(120)) {

                if (_colorBackground == _colorTarget) {
                    _colorTarget = _tft->C_BLUE;
                }
                else {
                    _colorTarget = _tft->C_RED;
                }

                //setBackground();
            }
            break;
        }
    }
}

void AppTorchRun::reset() {
    _option = 1;
    _canBeClosed = false;
    _colorTarget = _tft->C_WHITE;
    _colorBackground = _tft->C_RED;
}

/*
bool AppTorchRun::CanBeClosed() {
    return _canBeClosed;
}
*/
void AppTorchRun::setValue1(int16_t value) {
    _brightness = value;
}

void AppTorchRun::setButton1() {

    switch (_option) {
        case 1: {
            _colorTarget = _tft->C_WHITE;
            _option++;
            break;
        }
        case 2: {
            _colorTarget = _tft->C_RED;
            _option++;
            break;
        }
        case 3: {
            _colorTarget = _tft->C_BLUE;
            _option = 1;
            break;
        }
    }
}

void AppTorchRun::setButton2() {

    if (_mode < 2) {
        _mode++;
    }
    else {
        _mode = 1;
    }

    _modeAnimation1 = 0;
    _tft->fillScreen(_tft->C_BLACK);

    int positionX = 50;
    int positionY = 100;

    _tft->setFont(FontDefault);
    _tft->setCursor(positionX, positionY);
    _tft->setTextColor(_tft->C_GREEN);

    _tft->print("Mode");

    char buffer[12];
    sprintf(buffer, "%d", _mode);
    _tft->setCursor(positionX, positionY + 20);
    _tft->print(buffer);
}