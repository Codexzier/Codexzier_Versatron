//
// Created by codexzier on 03.06.26.
//




#ifndef CODEXZIER_VERSATRON_APPPICTUREVIEWER_H
#define CODEXZIER_VERSATRON_APPPICTUREVIEWER_H

#pragma once

#include <Arduino.h>
#include "BaseDrawable.h"

class AppPictureViewer : public BaseDrawable {

public:

    void initExtend() override{}
    void drawUpdate() override;
    void setButton1() override;
    void setButton2() override;
    void setButton3() override { _canBeClosed = true; }
    void setValue1(int16_t value) override {}
    void setValue2(int16_t value) override {}
    void reset() override {}

};

#endif //CODEXZIER_VERSATRON_APPPICTUREVIEWER_H
