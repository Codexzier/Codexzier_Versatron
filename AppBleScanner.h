//
// Created by johan on 26.05.2026.
//

#ifndef CODEXZIER_VERSATRON_APPBLESCANNER_H
#define CODEXZIER_VERSATRON_APPBLESCANNER_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"

#include "AppBleScannerResultList.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

class AppBleScanner {
    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    bool _hasDraw = false;
    void drawScanInfo();

    AppBleScannerResultList _resultList;
    int scanTime = 5; //In seconds
    BLEScan* pBLEScan;

public:
    AppBleScanner()
    : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0){ }

    void init(GC9A01_LTSM &tft,
        uint16_t colorOn,
        uint16_t colorOff,
        uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;

        _resultList.init(tft, _colorOn, _colorOff, _colorText);

        // TODO: Start instance if start this application
        BLEDevice::init("");
        pBLEScan = BLEDevice::getScan(); //create new scan
        pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
        pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
        pBLEScan->setInterval(100);
        pBLEScan->setWindow(99);  // less or equal setInterval value
    }

    /**
     * Draw content.
     */
    void drawUpdate();

    /**
     * Set all parameter to default.
     */
    void reset();

    /**
     * For the 3. Button to left the program.
     * @return Value are true, if the app can be closed.
     */
    bool CanBeClosed();

    void scan();

    void setButton1();
    void setButton2();
};


#endif //CODEXZIER_VERSATRON_APPBLESCANNER_H
