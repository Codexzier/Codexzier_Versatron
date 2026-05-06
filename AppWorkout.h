//
// Created by codexzier on 04.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWORKOUT_H
#define CODEXZIER_VERSATRON_APPWORKOUT_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"
#include "RingSegmentDisplay.h"


class AppWorkout {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    int _radiusOuter1 = 118;
    int _radiusInner1 = 112;
    int _radiusOuter2 = 108;
    int _radiusInner2 = 100;

    RingSegmentDisplay _ring1;
    RingSegmentDisplay _ring2;

    int _optionSetup = 1;
    int _option = 1;



    // timer variables
    int _startX = 50;
    int _startY = 70;
    void drawTimeValues(int x, int y, int value1, int value2);
    bool timerUpdate();
    long _lastTime = 0;
    int _seconds = 0;
    int _minutes = 0;

    void trainingUpdate();
    void drawTimeUp(int x, int y, int value, const char* text);
    int _secondsExecution = 0;
    int _secondsExecutionMax = 30;

    int _secondsBreak = 0;
    int _secondsBreakMax = 30;

    void drawRound();
    int _round = 1;
    int _roundMax = 5;

    // option 1 setup
    void drawOption1SetupTextAndTime(int x, int y, const char* text, int value);
    bool _option1SetupHasDraw = false;

public:
    AppWorkout()
        : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0),
            _ring1(_radiusOuter1, _radiusInner1),
            _ring2(_radiusOuter2, _radiusInner2){ }

    void init(GC9A01_LTSM &tft,
            const uint16_t colorOn,
            const uint16_t colorOff,
            const uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;

        _ring1.init(tft, _colorOn, _colorOff);
        _ring2.init(tft, _colorOn, _colorOff);
    }

    // base functions
    void drawUpdate();

    // individual functions
    void drawWorkoutOptions();
    void setOption(int option);

    void drawOption1Setup();
    void drawOption1() ;
};


#endif //CODEXZIER_VERSATRON_APPWORKOUT_H
