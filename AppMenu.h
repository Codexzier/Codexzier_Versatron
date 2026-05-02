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
    }

    void ResetInitializedDrawMenu() {
        _isInitializedDrawMenu = false;
        _menuIndex = 0;
    }

    void addItem(const MenuItem& item);
    void drawMenu();

    void setMenuIndex(int index);
    int getMenuIndex();



    ~AppMenu();
};

#endif //CODEXZIER_VERSATRON_APPMENU_H
