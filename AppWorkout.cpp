//
// Created by codexzier on 04.05.26.
//

#include "AppWorkout.h"
#include "GC9A01_LTSM.hpp"
#include <string>
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels

bool AppWorkout::timerUpdate() {

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

void AppWorkout::trainingUpdate() {

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

void AppWorkout::drawUpdate() {

    _ring1.drawGaugeUpdate();
    _ring2.drawGaugeUpdate();

    if (timerUpdate()) {
        return;
    }

    trainingUpdate();

    _ring1.setValue(_seconds);
    _ring2.setValue(_minutes);

    drawTimeValues(_startX + 30, 40, _minutes, _seconds);
}

void AppWorkout::drawRound() {
    _tft->setFont(FontArialBold);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    _tft->setCursor(_startX, _startY + 50);
    char buffer[10];
    sprintf(buffer, "Round %d", _round);
    _tft->print(buffer);
}

void AppWorkout::drawTimeUp(int x, int y, int value, const char* text) {
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    _tft->setCursor(x, y);

    char buffer[10];
    sprintf(buffer, "%02d", value);
    _tft->print(buffer);

    _tft->setCursor(x + 20, y);
    _tft->print(text);
}

void AppWorkout::drawTimeValues(int x, int y, int value1, int value2) {

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

void AppWorkout::drawWorkoutOptions() {

}

void AppWorkout::setOption(int option) {

}


// options
void AppWorkout::drawOption1() {
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