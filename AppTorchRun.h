//
// Created by codexzier on 22.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPTORCHRUN_H
#define CODEXZIER_VERSATRON_APPTORCHRUN_H

#include <Arduino.h>
#include <stdint.h>

#include "BaseDrawable.h"


class AppTorchRun : public BaseDrawable {

    int _option = 1;

    uint16_t _colorTarget = 1;
    int _mode = 1;
    int16_t _brightness = 0;
    int16_t _brightnessLast = 0;

    void setBackground();
    uint16_t _colorBackground = 1;
    void setCircleAnimation();
    bool animationRun(int animationEndCount);
    int _modeAnimation1 = 0;
    uint16_t _colorCircle = 0;

public:

    void initExtend() override {
        _applicationName = "Torch";
    }
    // base functions
    void drawUpdate() override;
    void reset() override;

    // Selection option - Color
    void setButton1() override;
    // accept setup - mode
    void setButton2() override;
    void setButton3() override { _canBeClosed = true; }

    void setValue1(int16_t value) override;
    void setValue2(int16_t value) override {}
};


#endif //CODEXZIER_VERSATRON_APPTORCHRUN_H
