//
// Created by codexzier on 04.05.26.
//

#include "AppWorkout.h"
#include "GC9A01_LTSM.hpp"
#include <string>
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels

void AppWorkout::drawUpdate() {

    // draw option
    if (!_optionRun) {
        // TODO: Set Option Setup
        _setup.drawUpdate();
        return;
    }

    _run.drawUpdate();
}

void AppWorkout::setValue1(int16_t value) {
    if (!_optionRun) {
        // TODO: Set Option Setup
        _setup.setValue1(value);
        return;
    }
}

void AppWorkout::setButton1() {
    if (!_optionRun) {
        // TODO: Set Option Setup
        _setup.setButton1();
        return;
    }
}
