//
// Created by codexzier on 01.05.26.
//

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <memory>

#include "GC9A01_LTSM.hpp"
#include "MenuPaging.h"

#ifndef CODEXZIER_VERSATRON_APPMENU_H
#define CODEXZIER_VERSATRON_APPMENU_H

class MenuItem {

public:
    std::string MenuName;
    std::string MenuDescription;

    bool isSelected = false;
};

class AppMenu {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;

    int _menuIndex = 0;

    int _menuIndexPageSelected = 1;
    int _menuIndexPage = 1;
    int _menuIndexPageMax = 1;

    int _menuX = 30;
    int _menuY1 = 50;
    int _menuY2 = 85;
    int _menuY3 = 120;
    int _menuY4 = 155;

    int _width = 180;
    int _height = 30;
    int _cornerRadius = 4;

    std::unique_ptr<std::vector<MenuItem*>> _menuItems;
    bool _isInitializedDrawMenu = false;

    MenuPaging _menuPaging;

public:
    AppMenu()
    : _tft(nullptr), _colorOn(0), _colorOff(0){}

    void init(
        GC9A01_LTSM &tft,
        const uint16_t colorOn,
        const uint16_t colorOff) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;

        _menuPaging.init(tft, _colorOn, _colorOff, tft.C_BEIGE, 85, 194);
    }

    void ResetInitializedDrawMenu() {
        _isInitializedDrawMenu = false;
        _menuIndex = 0;

        _menuIndexPage = 1;

        _menuPaging.drawFrameAndPage(_menuIndexPage, _menuIndexPageMax);
    }

    void addItem(const MenuItem& item);
    void drawMenu();

    void setMenuIndex(int index);
    int getMenuIndex();


    void drawDebugValue(int value);

    ~AppMenu();
};

#endif //CODEXZIER_VERSATRON_APPMENU_H
