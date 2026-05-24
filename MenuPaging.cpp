//
// Created by codexzier on 03.05.26.
//

#include "MenuPaging.h"
#include <string>
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels

void MenuPaging::setPage(int pageNumber) {
    char buffer[12];
    sprintf(buffer, "%d", pageNumber);

    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->setCursor(_positionX + 10, _positionY + 4);
    _tft->print(buffer);
}

void MenuPaging::setPageAndPageMax(int pageNumber, int pageMax) {

    setPage(pageNumber);

    char buffer[12];
    sprintf(buffer, "%d", pageMax);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->setCursor(_positionX + 45, _positionY + 4);
    _tft->print(buffer);
}

void MenuPaging::drawFrameAndPage(int pageNumber, int pageMax) {

    _tft->setFont(FontArialBold);

    const int width = 70;
    _tft->drawRoundRect(_positionX, _positionY, width, 24, _cornerRadius, _colorOff);
    _tft->drawLine(_positionX + 34, _positionY, _positionX + 34, _positionY + 22, _colorOff);

    setPageAndPageMax(pageNumber, pageMax);
}
