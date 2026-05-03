//
// Created by codexzier on 26.04.26.
//
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"
#include "AppMenu.h"
#include "RingSegmentDisplay.h"

#ifndef CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
#define CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H

class Codexzier_Versatron {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;

    // ========================================================================================
    // app menu
    AppMenu _appMenu;

    // ========================================================================================
    // Workout Helper
    int _radiusOuter1 = 118;
    int _radiusInner1 = 112;
    int _radiusOuter2 = 108;
    int _radiusInner2 = 100;

    RingSegmentDisplay mRing1;
    RingSegmentDisplay mRing2;


public:
    Codexzier_Versatron()
        : _tft(nullptr), _colorOn(0), _colorOff(0),
            mRing1(_radiusOuter1, _radiusInner1),
            mRing2(_radiusOuter2, _radiusInner2) {
    }

    void init(GC9A01_LTSM &tft,
        const uint16_t colorOn,
        const uint16_t colorOff)
    {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;

        _appMenu.init(tft, _colorOn, _colorOff);


        mRing1.init(tft, _colorOn, _colorOff);
        mRing2.init(tft, _colorOn, _colorOff);
    }

    void drawMenuAppUi();
    void addMenuItem(const MenuItem& item);
    void setMenuSelect(int index)
    {
        _appMenu.setMenuSelect(index);
    }

    void drawWorkoutAppUi();
};

#endif //CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
