//
// Created by codexzier on 04.05.26.
//

#include "AppWorkout.h"
#include "GC9A01_LTSM.hpp"
#include <string>

void AppWorkout::initExtend() {
    _setup.init(*_tft, _colorOn, _colorOff, _colorText);
    _run.init(*_tft, _colorOn, _colorOff, _colorText);

    _applicationName = "Workout";
}


void AppWorkout::drawUpdate() {

    // draw option
    if (!_optionRun) {
        // TODO: Set Option Setup
        _setup.drawUpdate();
        return;
    }

    _run.drawUpdate();
}

void AppWorkout::reset() {
    _option = 1;
    _optionRun = false;
    _setup.reset();
    _run.reset();

    _tft->clearBuffer(_tft->C_BLACK);
}

void AppWorkout::setValue1(int16_t value) {

    value = value / 60;
    if(value > 60) {
        value = 60;
    }
    value = 60 - value;

    if (!_optionRun) {
        _setup.setValue1(value);
        return;
    }
}

void AppWorkout::setButton1() {

    if (!_optionRun) {

        _setup.setButton1();
        return;
    }
}

void AppWorkout::setButton2() {

    if (!_optionRun) {

        // TODO: Fragen ob wirklich gestartet werden soll.

        _tft->fillScreen(_tft->C_BLACK);

        _run.setOptionRun(
            _setup.getExecutionMax(),
            _setup.getBreakMax(),
            _setup.getRoundMax());
        _optionRun = true;
        return;
    }
}