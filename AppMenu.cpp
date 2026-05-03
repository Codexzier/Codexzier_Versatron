//
// Created by codexzier on 01.05.26.
//

#include "AppMenu.h"
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels


void AppMenu::addItem(const MenuItem& item) {

    if (!_menuItems) {
        _menuItems = std::make_unique<std::vector<MenuItem*>>();
    }

    // Erstelle eine Kopie des MenuItem-Objekts auf dem Heap
    MenuItem* newItem = new MenuItem;
    newItem->MenuName = item.MenuName;          // std::string kopiert automatisch
    newItem->MenuDescription = item.MenuDescription;

    // Füge den Zeiger zum Vector hinzu
    _menuItems->push_back(newItem);

    _menuPaging.drawFrameAndPage(_menuIndexPage, _menuIndexPageSelected);

    float maxIndexPage1 = static_cast<int>(_menuItems->size()) / 4.0f;
    int maxIndexPage2 = static_cast<int>(_menuItems->size()) / 4;

    if (maxIndexPage1 > (float)maxIndexPage2) {
        maxIndexPage2++;
    }

    _menuIndexPageMax = maxIndexPage2;
}

void AppMenu::drawMenu() {

    if (!_menuItems) {
        return;
    }

    if (_menuIndexPage != _menuIndexPageSelected) {
        _isInitializedDrawMenu = false;
        _tft->fillScreen(_tft->C_BLACK);
    }
    _menuIndexPageSelected = _menuIndexPage;

    const int maxEntries = 4;
    const int yPositions[] = {_menuY1, _menuY2, _menuY3, _menuY4};
    bool nothing = false;

    for (int i = 0; i < maxEntries; ++i) {

        int indexItem = i + ((_menuIndexPage - 1) * 4);
        if (indexItem < 0 || indexItem >= static_cast<int>(_menuItems->size())) {
            nothing = true;
        }

        if (nothing) {
            continue;
        }

        bool isSelected = (indexItem == _menuIndex);
        uint16_t color = isSelected ? _colorOn : _colorOff;
        _tft->drawRoundRect(_menuX, yPositions[i], _width, _height, _cornerRadius, color);

        MenuItem* item = (*_menuItems)[indexItem];
        if (_isInitializedDrawMenu && item->isSelected == isSelected) {
            continue;
        }

        item->isSelected = isSelected;

        _tft->setFont(FontArialBold);
        _tft->setTextColor(color, _tft->C_BLACK);
        _tft->setCursor(_menuX + 10, yPositions[i] + 6);
        _tft->print(item->MenuName.c_str());
    }

    if (_isInitializedDrawMenu) {
        _menuPaging.setPage(_menuIndexPage);
    }
    else {
        _menuPaging.drawFrameAndPage(_menuIndexPage, static_cast<int>(_menuItems->size()));
    }

    _isInitializedDrawMenu = true;
}

void AppMenu::setMenuIndex(int index) {

    if (index < 0 || index >= static_cast<int>(_menuItems->size()))
        return;

    _menuIndex = index;
    _menuIndexPage = index > 3 ? 2 : 1;
    drawMenu();
}

int AppMenu::getMenuIndex() {
    return _menuIndex;
}

void AppMenu::drawDebugValue(int value) {

    _tft->setFont(FontDefault);
    _tft->setTextColor(_tft->C_GREEN, _tft->C_BLACK);
    _tft->setCursor(180, 120);

    char buffer[12];
    sprintf(buffer, "%d", value);
    _tft->print(buffer);
}

AppMenu::~AppMenu() {
    if (_menuItems) {
        for (MenuItem* item : *_menuItems) {
            delete item;
        }
    }
}
