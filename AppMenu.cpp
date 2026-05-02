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
}

void AppMenu::drawMenu() {

    if (!_menuItems) {
        return;
    }

    const int maxEntries = 4;
    const int yPositions[] = {_menuY1, _menuY2, _menuY3, _menuY4};

    _tft->setFont(FontArialBold);
    for (int i = 0; i < maxEntries && i < static_cast<int>(_menuItems->size()); ++i) {

        MenuItem* item = (*_menuItems)[i];
        if (_isInitializedDrawMenu && item->isSelected == (i == _menuIndex)) {
            continue;
        }

        item->isSelected = (i == _menuIndex);

        uint16_t color = (i == _menuIndex) ? _colorOn : _colorOff;
        _tft->drawRoundRect(_menuX, yPositions[i], _width, _height, _cornerRadius, color);
        _tft->setTextColor(color, _tft->C_BLACK);
        _tft->setCursor(_menuX + 10, yPositions[i] + 6);
        _tft->print(item->MenuName.c_str());
    }

    if (!_isInitializedDrawMenu) {
        _tft->drawRoundRect(100, 196, 34, 24, _cornerRadius, _tft->C_BEIGE);
    }

    _tft->setTextColor(_colorOff, _tft->C_BLACK);
    _tft->setCursor(110, 200);

    char buffer[12];
    sprintf(buffer, "%d", _menuIndex + 1);
    _tft->print(buffer);

    _isInitializedDrawMenu = true;
}

void AppMenu::setMenuIndex(int index) {

    if (index < 0 || index >= static_cast<int>(_menuItems->size()))
        return;

    _menuIndex = index;
    drawMenu();
}

int AppMenu::getMenuIndex() {
    return _menuIndex;
}

AppMenu::~AppMenu() {
    if (_menuItems) {
        for (MenuItem* item : *_menuItems) {
            delete item;
        }
    }
}
