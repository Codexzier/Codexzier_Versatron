//
// Created by codexzier on 01.05.26.
//

#include "MenuArea.h"
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels


void MenuArea::drawUpdate() {

    // draw only if menu items exists
    if (!_menuItems) {
        return;
    }

    drawInputValues();
    drawMenu();
}

// not sure if this is the best approach
void MenuArea::setMaxIndexPage() {
    float maxIndexPage1 = static_cast<int>(_menuItems->size()) / 4.0f;
    int maxIndexPage2 = static_cast<int>(_menuItems->size()) / 4;

    if (maxIndexPage1 > (float)maxIndexPage2) {
        maxIndexPage2++;
    }

    _menuIndexPageMax = maxIndexPage2;
}

void MenuArea::setIndexPage() {
    // get the current index page based on the menu index
    // example: is index 1, it is page 1 and it is index 4, it is page 2.
    const float current = (static_cast<float>(_menuIndex) + 1.0f) / 4.0f;
    int currentInt = (_menuIndex + 1) / 4;

    if (current > static_cast<float>(currentInt)) {
        currentInt++;
    }

    _menuIndexPage = currentInt;
}

void MenuArea::addItem(const MenuItem& item) {

    if (!_menuItems) {
        _menuItems = std::make_unique<std::vector<MenuItem*>>();
    }

    // Erstelle eine Kopie des MenuItem-Objekts auf dem Heap
    MenuItem* newItem = new MenuItem;
    newItem->MenuName = item.MenuName;          // std::string kopiert automatisch
    newItem->MenuDescription = item.MenuDescription;

    // Füge den Zeiger zum Vector hinzu
    _menuItems->push_back(newItem);

    _menuPaging.drawFrameAndPage(_menuIndexPage, _menuIndexPageMax);

    setMaxIndexPage();
}

void MenuArea::drawMenu() {

    drawClearByChangedPage();

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

        MenuItem* item = (*_menuItems)[indexItem];
        if (_isInitializedDrawMenu && item->isSelected == isSelected) {
            continue;
        }

        uint16_t color = isSelected ? _colorOn : _colorOff;
        _tft->drawRoundRect(_menuX, yPositions[i], _width, _height, _cornerRadius, color);
        item->isSelected = isSelected;

        _tft->setFont(FontArialBold);
        _tft->setTextColor(color, _tft->C_BLACK);
        _tft->setCursor(_menuX + 10, yPositions[i] + 6);
        _tft->print(item->MenuName.c_str());
    }

    drawMenuPaging();

    _isInitializedDrawMenu = true;
}


void MenuArea::drawClearByChangedPage() {

    if (_menuIndexPage != _menuIndexPageSelected) {
        _isInitializedDrawMenu = false;
        _tft->fillScreen(_tft->C_BLACK);
    }

    _menuIndexPageSelected = _menuIndexPage;
}

void MenuArea::drawMenuPaging() {

    _menuPaging.drawFrameAndPage(_menuIndexPage, _menuIndexPageMax);
}

void MenuArea::setButton1() {
    if (_menuIndex < 0 || _menuIndex >= static_cast<int>(_menuItems->size()))
    {
        _menuIndex = 0;
    }
    else {
        _menuIndex++;
    }

    setIndexPage();

    _isInitializedDrawMenu = false;
}

int MenuArea::getMenuSelectIndex() {
    return _menuIndex;
}

void MenuArea::drawInputValues() {

    _tft->setFont(FontDefault);
    _tft->setTextColor(_tft->C_DGREY, _tft->C_BLACK);
    _tft->setCursor(80, 30);

    char buffer[12];
    sprintf(buffer, "%d", _value1);
    _tft->print(buffer);

    _tft->setCursor(140, 30);
    sprintf(buffer, "%d", _value2);
    _tft->print(buffer);
}

void MenuArea::reset() {
    _isInitializedDrawMenu = false;
    _menuIndex = 0;
    _menuIndexPage = 1;
    //_menuPaging.drawFrameAndPage(_menuIndexPage, _menuIndexPageMax);
}


MenuArea::~MenuArea() {
    if (_menuItems) {
        for (MenuItem* item : *_menuItems) {
            delete item;
        }
    }
}
