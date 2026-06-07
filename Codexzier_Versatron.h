//
// Created by codexzier on 26.04.26.
//
#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "AppBleScanner.h"
#include "AppPictureViewer.h"
#include "GC9A01_LTSM.hpp"

#include "MenuArea.h"
#include "AppWorkout.h"
#include "AppTorchRun.h"
#include "AppWlanScanner.h"

#ifndef CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
#define CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H

enum DrawContent {
    Menu = 0,
    Workout = 1,
    Torch = 2,
    ScanWiFi = 3,
    ScanBle = 4,
    PictureViewer = 5
};

class Codexzier_Versatron {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    DrawContent _drawContent = Menu;

    // ========================================================================================
    // app menu
    MenuArea _menu;

    // ========================================================================================
    // Workout Helper
    AppWorkout _appWorkout;

    // ========================================================================================
    // Torch
    AppTorchRun _appTorch;

    // ========================================================================================
    // ScanWifi
    AppWlanScanner _appScnWiFi;
    AppBleScanner _appScnBle;

    AppPictureViewer _appPictureViewer;


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
        _menu.initExtend();
        _appWorkout.init(tft, _colorOn, _colorOff, colorText);
        _appWorkout.initExtend();
        _appTorch.init(tft, _colorOn, _colorOff, colorText);
        _appScnWiFi.init(tft, _colorOn, _colorOff, colorText);
        _appScnWiFi.initExtend();
        _appScnBle.init(tft, _colorOn, _colorOff, colorText);
        _appScnBle.initExtend();
        _appPictureViewer.init(tft, colorOn, colorOff, colorText);
    }

    void drawUpdate();

    void showMenuAppUi();
    void addMenuItem(const MenuItem& item);

    void showApp(DrawContent content);
    void setValue1(int16_t value);
    void setValue2(int16_t value) ;
    void setButton1();
    void setButton2();
    void setButton3();
};

#endif //CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
