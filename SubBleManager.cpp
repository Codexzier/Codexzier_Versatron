//
// Created by codexzier on 24.06.26.
//

#include "SubBleManager.h"

void SubBleManager::init() {

    BLEDevice::init("");
    _BLEScan = BLEDevice::getScan(); //create new scan
    _BLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    _BLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    _BLEScan->setInterval(100);
    _BLEScan->setWindow(99);  // less or equal setInterval value

    _hasSign = true;
}

BleScanResult SubBleManager::scan() {


    _foundDevices = _BLEScan->start(_scanTime, false);
    BleScanResult result ;
    result.CountDevice = _foundDevices->getCount();

    if (result.CountDevice == 0) {

        result.Success = false;
        return result;
    }

    result.Success = true;
    return result;
}

BleItem* SubBleManager::getBleItem(const int index) {

    BLEAdvertisedDevice device = _foundDevices->getDevice(index);

    BleItem* item = new BleItem;
    item->Name = device.getName().c_str();
    item->Address = device.getAddress().toString().c_str();

    item->HasDevUUID = false;
    if (device.haveServiceUUID()) {
        BLEUUID devUUID = device.getServiceUUID();
        item->DevUUID = devUUID.toString().c_str();
        item->HasDevUUID = true;
    }

    item->HasManufacturerData = false;
    if (device.haveManufacturerData()) {
        item->HasManufacturerData = true;
        item->ManufacturerData = device.getManufacturerData().c_str();
    }

    item->Rssi = device.getRSSI();

    return item;
}
