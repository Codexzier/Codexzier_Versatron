//
// Created by codexzier on 24.06.26.
//

#ifndef CODEXZIER_VERSATRON_SUBBLEMANAGER_H
#define CODEXZIER_VERSATRON_SUBBLEMANAGER_H
#include <HardwareSerial.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "AppBleScannerResultList.h"

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

class BleScanResult {
public:
    bool Success;
    int CountDevice;
};

class SubBleManager {

    BLEScan* _BLEScan;
    const int _scanTime = 2;
    BLEScanResults* _foundDevices;
    bool _hasSign = false;

public:
    void init();

    BleScanResult scan();
    BleItem* getBleItem(int index);
    bool IsReady() const { return _hasSign; }
};


#endif //CODEXZIER_VERSATRON_SUBBLEMANAGER_H
