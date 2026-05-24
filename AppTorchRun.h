//
// Created by codexzier on 22.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPTORCHRUN_H
#define CODEXZIER_VERSATRON_APPTORCHRUN_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"
#include "fonts_LTSM/FontPico_LTSM.hpp" // 8x12 pixels
#include "fonts_LTSM/FontSinclairS_LTSM.hpp" // 8x8 pixels


class AppTorchRun {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    int _option = 1;
    bool _canBeClosed = false;

    uint16_t _colorTarget = 1;
    int _mode = 1;
    int16_t _brightness = 0;

    void setBackground();
    uint16_t _colorBackground = 1;
    void setCircleAnimation();
    bool animationRun(int animationEndCount);
    int _modeAnimation1 = 0;
    uint16_t _colorCircle = 0;

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

        _colorTarget = tft.C_WHITE;
        _colorBackground = tft.C_RED;
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
