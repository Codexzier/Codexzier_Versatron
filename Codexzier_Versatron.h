//
// Created by codexzier on 26.04.26.
//
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"

#include "AppMenu.h"
#include "AppWorkout.h"

#ifndef CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
#define CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H

class Codexzier_Versatron {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    // ========================================================================================
    // app menu
    AppMenu _appMenu;

    // ========================================================================================
    // Workout Helper
    AppWorkout _appWorkout;


public:
    Codexzier_Versatron()
        : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0) { }

    void init(GC9A01_LTSM &tft,
        const uint16_t colorOn,
        const uint16_t colorOff,
        const uint16_t colorText)
    {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;

        _appMenu.init(tft, _colorOn, _colorOff);
        _appWorkout.init(tft, _colorOn, _colorOff, colorText);
    }

    void drawMenuAppUi();
    void addMenuItem(const MenuItem& item);
    void setMenuSelect(int index)
    {
        _appMenu.setMenuSelect(index);
    }

    void drawWorkoutAppUi();
    void drawWorkoutAppNextOption();
    void setWorkoutAppRun();

    void drawUpdate();
};

#endif //CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
