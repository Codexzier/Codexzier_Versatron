//
// Created by codexzier on 03.06.26.
//




#ifndef CODEXZIER_VERSATRON_APPPICTUREVIEWER_H
#define CODEXZIER_VERSATRON_APPPICTUREVIEWER_H

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "BaseDrawable.h"
#include "GC9A01_LTSM.hpp"

class AppPictureViewer : public BaseDrawable {

public:

    void initExtend() override{}
    void drawUpdate() override;
    void setButton1() override;
    void setButton2() override;

};

#endif //CODEXZIER_VERSATRON_APPPICTUREVIEWER_H
