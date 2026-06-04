//
// Created by codexzier on 04.05.26.
//

#include "AppWorkout.h"
#include "GC9A01_LTSM.hpp"
#include <string>
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels

void AppWorkout::initExtend() {
    _setup.init(*_tft, _colorOn, _colorOff, _colorText);
    _run.init(*_tft, _colorOn, _colorOff, _colorText);
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
    //_canBeClosed = false;
    _setup.reset();
    _run.reset();
}

void AppWorkout::setValue1(int16_t value) {

    // TODO: noch in eigene Function verschieben.
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

/*
void AppWorkout::setButton3() {

    if (_option) {

        _tft->fillScreen(_tft->C_BLACK);
        reset();

        return;
    }

    // TODO: Zurück zum Hauptmenü bzw. App verlassen
    _canBeClosed = true;
}
*/