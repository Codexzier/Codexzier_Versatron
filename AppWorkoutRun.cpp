//
// Created by codexzier on 11.05.26.
//

#include "AppWorkoutRun.h"

#include <cstdio>

#include "fonts_LTSM/FontArialBold_LTSM.hpp"

void AppWorkoutRun::drawUpdate() {

    _ring1.drawGaugeUpdate();
    _ring2.drawGaugeUpdate();

    if (timerUpdate()) {
        return;
    }

    _ring1.setValue(_seconds);
    _ring2.setValue(_minutes);

    drawTimeValues(_startX + 32, 40, _minutes, _seconds);
    trainingUpdate();

    _drawRoundHasDraw = true;
}

bool AppWorkoutRun::timerUpdate() {
    long actualTime = millis();
    if(actualTime <= _lastTime + 1000){
        return true;
    }
    _lastTime = actualTime;

    if (_seconds > 59) {

        _seconds = 0;

        if (_minutes > 59) {
            _minutes = 0;
        }
        else {
            _minutes++;
        }
    }
    else {
        _seconds++;
    }

    return false;
}

void AppWorkoutRun::trainingUpdate() {
    _tft->setFont(FontDefault);
    int timeUpExecution = _secondsExecutionMax;
    int timeUpBreak = _secondsBreakMax;
    if (_secondsExecution <= _secondsExecutionMax) {
        timeUpExecution = _secondsExecutionMax - _secondsExecution;
        _secondsExecution++;
    }
    else {
        if (_secondsBreak <= _secondsBreakMax ) {
            timeUpBreak = _secondsBreakMax - _secondsBreak;
            _secondsBreak++;
        }
        else {
            _secondsExecution = 0;
            _secondsBreak = 0;
            _round++;
        }
    }

    drawTimeUp(_startX, _startY + 10, timeUpExecution, "Execution");
    drawTimeUp(_startX, _startY + 25, timeUpBreak, "Break");
    drawRound();
}

void AppWorkoutRun::drawTimeValues(int x, int y, int value1, int value2) {
    _tft->setFont(FontArialBold);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    char buffer[3];
    sprintf(buffer, "%02d", value1);
    _tft->setCursor(x, y);
    _tft->print(buffer);

    _tft->setCursor(x + 30, y);
    _tft->print(":");
    sprintf(buffer, "%02d", value2);
    _tft->setCursor(x + 45, y);
    _tft->print(buffer);
}

void AppWorkoutRun::drawRound() {
    _tft->setFont(FontArialBold);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    if (!_drawRoundHasDraw) {
        _tft->setCursor(_startX, _startY + 50);
        _tft->print("Round");
    }

    _tft->setCursor(_startX + 100, _startY + 50);
    char buffer[10];
    sprintf(buffer, "%d", _round);
    _tft->print(buffer);
}

void AppWorkoutRun::drawTimeUp(int x, int y, int value, const char *text) {
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    _tft->setCursor(x, y);

    char buffer[10];
    sprintf(buffer, "%02d", value);
    _tft->print(buffer);

    if (!_drawRoundHasDraw) {
        _tft->setCursor(x + 20, y);
        _tft->print(text);
    }
}


void AppWorkoutRun::setOptionRun() {
    _drawRoundHasDraw = false;

    _secondsExecution = 0;
    _secondsBreak = 0;
    _round = 1;
    _seconds = 0;
    _minutes = 0;

    drawOption1Run();
}

void AppWorkoutRun::drawOption1Run() {
    _ring1.drawInitGauge();
    _ring2.drawInitGauge();

    _ring1.setValue(0);
    _ring2.setValue(0);

    _secondsExecution = 0;
    _secondsBreak = 0;

    _tft->drawFastHLine(_startX, _startY, 140, _colorText);
    drawTimeUp(_startX, _startY + 10, _secondsExecutionMax, "Execution");
    drawTimeUp(_startX, _startY + 25, _secondsBreakMax, "Break");
    _tft->drawFastHLine(_startX, _startY + 40, 140, _colorText);
    drawRound();

    _tft->drawCircle(120, 120, 99, _colorOn);
    _tft->drawCircle(120, 120, 98, _colorOn);
    _tft->drawCircle(120, 120, 97, _colorOff);
}