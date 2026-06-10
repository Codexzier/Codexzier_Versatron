//
// Created by codexzier on 01.05.26.
//

#pragma once

#include <Arduino.h>
#include <vector>
#include <string>
#include <memory>

#include "BaseDrawable.h"
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

class MenuArea : public BaseDrawable {

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

    void setMaxIndexPage();
    void setIndexPage();

    void drawMenu();
    void drawClearByChangedPage();
    void drawMenuPaging();

    void drawInputValues();
    int _value1 = 0;
    int _value2 = 0;

public:

    void initExtend() override {
        _menuPaging.init(*_tft, _colorOn, _colorOff, _tft->C_BEIGE, 85, 194);
    }
    void drawUpdate() override;

    /**
     * Jump to the next select menu item.
     */
    void setButton1() override;
    void setButton2() override{}
    void setButton3() override { _canBeClosed = true; }

    void reset() override;

    void setValue1(int16_t value) override {
        _value1 = value;
    }
    void setValue2(int16_t value) override {
        _value2 = value;
    }

    bool CanBeClosed() override {
        // Menu is the base level
        return false;
    }

    bool IsMenu() override {
        return true;
    }

    /**
     * Add an menu item for selection an application.
     * @param item Item for selection application.
     */
    void addItem(const MenuItem& item);

    /**
     * Get the index number of the selected menu item.
     * @return Index number of selected menue item.
     */
    int getMenuSelectIndex();

    /**
     * Destruct this menu class instance.
     */
    ~MenuArea() override;
};

#endif //CODEXZIER_VERSATRON_APPMENU_H
