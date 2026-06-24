//
// Created by codexzier on 23.06.26.
//

#ifndef CODEXZIER_VERSATRON_APPCAMERAONDISPLAY_H
#define CODEXZIER_VERSATRON_APPCAMERAONDISPLAY_H

#include "BaseDrawable.h"
#include <SubCameraManager.h>

class AppCameraOnDisplay : public BaseDrawable {

    void drawPicture(const uint8_t* bitmap);
    SubCameraManager* _cameraManager = nullptr;

public:
    void initExtend() override {}
    void drawUpdate() override;
    void setButton1() override {}
    void setButton2() override {}
    void setButton3() override { _canBeClosed = true; }
    void setValue1(int16_t value) override {}
    void setValue2(int16_t value) override {}
    void reset() override {
        _hasDraw = false;
    }

    void SetupCameraManager(SubCameraManager &cameraManager) {
        _cameraManager = &cameraManager;
    }
};

#endif //CODEXZIER_VERSATRON_APPCAMERAONDISPLAY_H
