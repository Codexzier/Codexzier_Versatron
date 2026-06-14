//
// Created by codexzier on 11.05.26.
//

#include "AppWorkoutRun.h"
#include <cstdio>
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"

void AppWorkoutRun::drawUpdate() {

    if (_workoutFinish) {

        if (_renderWorkoutFinish) {
            return;
        }

        _tft->fillRect(50, 80, 140, 80, _tft->C_BLACK);
        _tft->drawRoundRect(50, 80, 140, 80, 4, _colorOn);

        _tft->setFont(FontArialBold);
        _tft->setTextColor(_colorText, _tft->C_BLACK);
        _tft->setCursor(64, 100);
        _tft->print("Workout");
        _tft->setCursor(64, 120);
        _tft->print("Finish");

        _renderWorkoutFinish = true;
        return;
    }

    _ring1.drawGaugeUpdate();
    _ring2.drawGaugeUpdate();

    if (timerUpdate()) {
        return;
    }

    if (_secondsExecution < _secondsExecutionMax) {
        _ring1.setColor(_tft->C_GREEN);
    }
    else if (_secondsBreak < _secondsBreakMax) {
        _ring1.setColor(_tft->C_ORANGE);
    }

    _ring1.setValue(_secondsExecution + _secondsBreak + 1);
    _ring2.setValue(_round);

    drawTimeValues(_startX + 32, 40, _minutes, _seconds);
    trainingUpdate();

    _drawRoundHasDraw = true;
}

void AppWorkoutRun::reset() {
    _drawRoundHasDraw = false;
    _workoutFinish = false;
    _renderWorkoutFinish = false;

    _tft->clearBuffer(_tft->C_BLACK);
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
    _timeUpExecution = _secondsExecutionMax;
    _timeUpBreak = _secondsBreakMax;

    updateExecutionAndBreak();

    drawTimeUp(_startX, _startY + 10, _timeUpExecution, "Execution");
    drawTimeUp(_startX, _startY + 25, _timeUpBreak, "Break");
    drawRound();
}

void AppWorkoutRun::updateExecutionAndBreak() {

    if (_secondsExecution < _secondsExecutionMax) {
        _timeUpExecution = _secondsExecutionMax - _secondsExecution;
        _secondsExecution++;
    }
    else {

        if (_secondsBreak < _secondsBreakMax) {
            _timeUpBreak = _secondsBreakMax - _secondsBreak;
            _secondsBreak++;
        }
        else  {
            _secondsExecution = 0;
            _secondsBreak = 0;
            _ring1.setValue(0);
            _round++;

            if (_round > _roundMax) {
                _workoutFinish = true;
            }
        }
    }
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


void AppWorkoutRun::setOptionRun(int16_t executionMax, int16_t breakMax, int16_t roundMax) {

    _tft->clearBuffer(_tft->C_BLACK);

    _secondsExecutionMax = executionMax;
    _secondsBreakMax = breakMax;
    _roundMax = roundMax;

    _drawRoundHasDraw = false;
    _workoutFinish = false;
    _renderWorkoutFinish = false;

    _secondsExecution = 0;
    _secondsBreak = 0;
    _round = 1;
    _seconds = 0;
    _minutes = 0;

    drawOptionRun();
}

void AppWorkoutRun::drawOptionRun() {

    _ring1.drawInitGaugeSetup(_secondsExecutionMax + _secondsBreakMax);
    _ring2.drawInitGaugeSetup(_roundMax);

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