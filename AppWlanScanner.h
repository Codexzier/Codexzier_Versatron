//
// Created by codexzier on 25.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWLANSCANNER_H
#define CODEXZIER_VERSATRON_APPWLANSCANNER_H

#include <Arduino.h>
#include "WiFi.h"
#include "AppWlanScannerResultList.h"
#include "BaseDrawable.h"


class AppWlanScanner : public BaseDrawable {

    void drawScanInfo();

    AppWlanScannerResultList _resultList;

    void scanWifi();

public:
    void initExtend() override {
        _resultList.init(*_tft, _colorOn, _colorOff, _colorText);
        WiFi.STA.begin();
        _applicationName = "WLAN Scanner";
    }
    void drawUpdate() override;
    void setButton1() override;
    void setButton2() override;
    void setButton3() override { _canBeClosed = true; }
    void setValue1(int16_t value) override {}
    void setValue2(int16_t value) override {}
    void reset() override;
};


#endif //CODEXZIER_VERSATRON_APPWLANSCANNER_H
