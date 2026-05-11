//
// Created by codexzier on 10.05.26.
//

#include "AppWorkoutSetup.h"

#include <cstdio>

#include "fonts_LTSM/FontArialBold_LTSM.hpp"

void AppWorkoutSetup::drawUpdate() {

    if (!_option1SetupHasDraw) {
        _tft->drawCircle(120, 120, 99, _colorOn);

        _tft->setCursor(_startX, _startY);
        _tft->setFont(FontArialBold);
        _tft->setTextColor(_colorText, _tft->C_BLACK);
        _tft->print("Workout");
        _tft->setCursor(_startX, _startY + 20);
        _tft->print("Setup");

        _tft->drawFastHLine(_startX, _startY + 45, 140, _colorText);
        _tft->drawFastHLine(_startX, _startY + 100, 140, _colorText);
    }

    drawSetupValues();
    drawSelectPointer();
    _option1SetupHasDraw = true;
}

void AppWorkoutSetup::setValue1(int16_t value) {

    switch (_selectSetup) {
        case TimeExecution: {
            _secondsExecutionMax = value;
            break;
        }
        case TimeBreak: {
            _secondsBreakMax = value;
            break;
        }
        case CountRound: {
            _roundMax = value;
            break;
        }
    }
}

void AppWorkoutSetup::setButton1() {

    switch (_selectSetup) {
        case TimeExecution: {
            _selectSetup = TimeBreak;
            break;
        }
        case TimeBreak: {
            _selectSetup = CountRound;
            break;
        }
        case CountRound: {
            _selectSetup = TimeExecution;
            break;
        }
    }
}

void AppWorkoutSetup::drawSetupValues() {
    drawTextAndTime(_startX, _startY + 50, "Execut", _secondsExecutionMax);
    drawTextAndTime(_startX, _startY + 65, "Break", _secondsBreakMax);
    drawTextAndTime(_startX, _startY + 80, "Rounds", _roundMax);
}

void AppWorkoutSetup::drawTextAndTime(int x, int y, const char *text, int value) {

    _tft->setFont(FontArialBold);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    if (!_option1SetupHasDraw) {
        _tft->setCursor(x, y);
        _tft->print(text);
    }

    _tft->setCursor(x + 100, y);
    char buffer[10];
    sprintf(buffer, "%02d", value);
    _tft->print(buffer);
}

void AppWorkoutSetup::drawSelectPointer() {

    int16_t y = _startY + 3;
    switch (_selectSetup) {
        case TimeExecution: {
            y += 50;
            break;
        }
        case TimeBreak: {
            y += 65;
            break;
        }
        case CountRound: {
            y += 80;
            break;
        }
    }

    int16_t x = _startX + 140;

    if (y != _lastSelectSetupPointerPositionY) {
        _tft->drawTriangle(
            x, _lastSelectSetupPointerPositionY,
            x - 5, _lastSelectSetupPointerPositionY + 3,
            x, _lastSelectSetupPointerPositionY + 6,
            _tft->C_BLACK);
    }
    _lastSelectSetupPointerPositionY = y;

    _tft->drawTriangle(x, y, x - 5, y + 3, x, y + 6, _colorOn);
}

// ==============================
// properties
int16_t AppWorkoutSetup::getExecutionMax() const {
    return _secondsExecutionMax;
}

int16_t AppWorkoutSetup::getBreakMax() const {
    return _secondsBreakMax;
}
int16_t AppWorkoutSetup::getRoundMx() const {
    return _roundMax;
}