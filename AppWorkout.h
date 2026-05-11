//
// Created by codexzier on 04.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWORKOUT_H
#define CODEXZIER_VERSATRON_APPWORKOUT_H

#include <Arduino.h>
#include <stdint.h>

#include "AppWorkoutRun.h"
#include "GC9A01_LTSM.hpp"
#include "ControlRingSegmentDisplay.h"
#include "AppWorkoutSetup.h"


class AppWorkout {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    int _option = 1;
    bool _optionRun = false;

    // Setup and run
    AppWorkoutSetup _setup;
    AppWorkoutRun _run;


public:
    AppWorkout()
        : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0){ }

    void init(GC9A01_LTSM &tft,
            const uint16_t colorOn,
            const uint16_t colorOff,
            const uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;

        _setup.init(tft, colorOn, colorOff, colorText);
        _run.init(tft, colorOn, colorOff, colorText);
    }

    // base functions
    void drawUpdate();

    void setValue1(int16_t value);
    void setButton1();


};


#endif //CODEXZIER_VERSATRON_APPWORKOUT_H
