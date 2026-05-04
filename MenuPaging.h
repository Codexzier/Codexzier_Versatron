//
// Created by codexzier on 03.05.26.
//

#ifndef CODEXZIER_VERSATRON_MENUPAGING_H
#define CODEXZIER_VERSATRON_MENUPAGING_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"

class MenuPaging {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;
    uint16_t _positionX = 10;
    uint16_t _positionY = 10;
    int _cornerRadius = 4;


public:
    MenuPaging()
    : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0){}

    void init(
            GC9A01_LTSM &tft,
            const uint16_t colorOn,
            const uint16_t colorOff,
            const uint16_t colorText,
            const uint16_t positionX,
            const uint16_t positionY) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;
        _positionX = positionX;
        _positionY = positionY;
    }

    void drawFrameAndPage(int pageNumber, int pageMax);

    void setPageAndPageMax(int pageNumber, int pageMax);
    void setPage(int pageNumber);
};


#endif //CODEXZIER_VERSATRON_MENUPAGING_H
