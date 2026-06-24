//
// Created by johan on 26.05.2026.
//

#ifndef CODEXZIER_VERSATRON_APPBLESCANNER_H
#define CODEXZIER_VERSATRON_APPBLESCANNER_H

#include <Arduino.h>
#include "AppBleScannerResultList.h"
//#include <BLEDevice.h>
//#include <BLEUtils.h>
//#include <BLEScan.h>
//#include <BLEAdvertisedDevice.h>
#include "BaseDrawable.h"
#include "SubBleManager.h"


class AppBleScanner : public BaseDrawable {

    void drawScanInfo();

    AppBleScannerResultList _resultList;
    int scanTime = 5; //In seconds
    //BLEScan* pBLEScan;

    void scan();
    SubBleManager* _bleManager = nullptr;

public:

    void initExtend() override;
    void drawUpdate() override;
    void setButton1() override;
    void setButton2() override;
    void setButton3() override { _canBeClosed = true; }
    void setValue1(int16_t value) override {}
    void setValue2(int16_t value) override {}
    void reset() override;

    void SetupBleManager(SubBleManager &bleManager) {
        _bleManager = &bleManager;
    }
};


#endif //CODEXZIER_VERSATRON_APPBLESCANNER_H
