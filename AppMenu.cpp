//
// Created by codexzier on 01.05.26.
//

#include "AppMenu.h"
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels

void AppMenu::drawMenu() {
    _tft->drawRoundRect(_menuX, _menuY1, _width, _height, _cornerRadius, _colorOn);
    _tft->drawRoundRect(_menuX, _menuY2, _width, _height, _cornerRadius, _colorOff);
    _tft->drawRoundRect(_menuX, _menuY3, _width, _height, _cornerRadius, _colorOff);

    _tft->setTextColor(_colorOn, _tft->C_BLACK);
    _tft->setFont(FontArialBold);

    _tft->setCursor(_menuX + 10, _menuY1 + 5);
    _tft->print("Workout");
    _tft->setCursor(_menuX + 10, _menuY2 + 5);
    _tft->print("Servo Test");
    _tft->setCursor(_menuX + 10, _menuY3 + 5);
    _tft->print("Camera");
}

void AppMenu::setMenuIndex(int index) {
    switch (index) {
        case 0:
            _tft->drawRoundRect(_menuX, _menuY1, _width, _height, _cornerRadius, _colorOn);
            _tft->drawRoundRect(_menuX, _menuY2, _width, _height, _cornerRadius, _colorOff);
            _tft->drawRoundRect(_menuX, _menuY3, _width, _height, _cornerRadius, _colorOff);
            break;
        case 1:
            _tft->drawRoundRect(_menuX, _menuY1, _width, _height, _cornerRadius, _colorOff);
            _tft->drawRoundRect(_menuX, _menuY2, _width, _height, _cornerRadius, _colorOn);
            _tft->drawRoundRect(_menuX, _menuY3, _width, _height, _cornerRadius, _colorOff);
            break;
        case 2:
            _tft->drawRoundRect(_menuX, _menuY1, _width, _height, _cornerRadius, _colorOff);
            _tft->drawRoundRect(_menuX, _menuY2, _width, _height, _cornerRadius, _colorOff);
            _tft->drawRoundRect(_menuX, _menuY3, _width, _height, _cornerRadius, _colorOn);
            break;
        default:
            _tft->drawRoundRect(_menuX, _menuY1, _width, _height, _cornerRadius, _colorOff);
            _tft->drawRoundRect(_menuX, _menuY2, _width, _height, _cornerRadius, _colorOff);
            _tft->drawRoundRect(_menuX, _menuY3, _width, _height, _cornerRadius, _colorOff);
            break;
    }
}

int AppMenu::getMenuIndex() {
    return _menuIndex;
}

AppMenu::~AppMenu() {

}
