//
// Created by codexzier on 10.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWORKOUTSETUP_H
#define CODEXZIER_VERSATRON_APPWORKOUTSETUP_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"


class AppWorkoutSetup {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;


    int _startX = 50;
    int _startY = 70;

    void drawOption1SetupTextAndTime(int x, int y, const char* text, int value);
    bool _option1SetupHasDraw = false;

    int _secondsExecutionMax = 30;
    int _secondsBreakMax = 30;
    int _roundMax = 5;


    void drawOptionSetup();

public:
    AppWorkoutSetup()
    : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0) {}

    void init(GC9A01_LTSM &tft,
            const uint16_t colorOn,
            const uint16_t colorOff,
            const uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;
    }

    // base functions
    void drawUpdate();
};


#endif //CODEXZIER_VERSATRON_APPWORKOUTSETUP_H
