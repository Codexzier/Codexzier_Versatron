//
// Created by codexzier on 26.04.26.
//
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"

#include "MenuArea.h"
#include "AppWorkout.h"

#ifndef CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
#define CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H

enum DrawContent {
    Menu,
    Workout
};

class Codexzier_Versatron {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    DrawContent _drawContent;

    // ========================================================================================
    // app menu
    MenuArea _menu;

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

        _menu.init(tft, _colorOn, _colorOff);
        _appWorkout.init(tft, _colorOn, _colorOff, colorText);
    }

    void showMenuAppUi();
    void addMenuItem(const MenuItem& item);
    void nextMenuSelect();

    // void setMenuSelect(int index)
    // {
    //     _menu.setMenuSelect(index);
    // }

    void drawWorkoutAppUi();
    void drawWorkoutAppNextOption();
    void setWorkoutAppRun();

    void drawUpdate();
};

#endif //CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
