//
// Created by codexzier on 04.06.26.
//

#ifndef CODEXZIER_VERSATRON_BASEDRAWABLE_H
#define CODEXZIER_VERSATRON_BASEDRAWABLE_H

#pragma once
#include "IDrawable.h"

class BaseDrawable : public IDrawable {

public:
    void init(
            GC9A01_LTSM &tft,
            const uint16_t colorOn,
            const uint16_t colorOff,
            const uint16_t colorText) override {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = _colorText;
    }

    /**
     * For the 3. Button to left the program.
     * @return Value are true, if the app can be closed.
     */
    bool CanBeClosed() override {
        return _canBeClosed;
    }
};

#endif //CODEXZIER_VERSATRON_BASEDRAWABLE_H
