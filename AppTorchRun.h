//
// Created by codexzier on 22.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPTORCHRUN_H
#define CODEXZIER_VERSATRON_APPTORCHRUN_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"


class AppTorchRun {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    int _option = 1;
    bool _canBeClosed = false;

    uint16_t _color;
    int _mode = 1;
    int16_t _brightness = 0;

    void setBackground();
    uint16_t _colorBackground;
    void setMode();

public:
    AppTorchRun()
    : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0){ }

    void init(GC9A01_LTSM &tft,
                const uint16_t colorOn,
                const uint16_t colorOff,
                const uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;
    }

    // base functions
    void drawUpdate();
    void reset();
    bool CanBeClosed();

    void setValue1(int16_t value);

    // Selection option - Color
    void setButton1();
    // accept setup - mode
    void setButton2();
    // Return
    void setButton3();
};


#endif //CODEXZIER_VERSATRON_APPTORCHRUN_H
