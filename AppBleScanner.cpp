//
// Created by johan on 26.05.2026.
//

#include "AppBleScanner.h"

void AppBleScanner::initExtend() {

    _resultList.init(*_tft, _colorOn, _colorOff, _colorText);
    // TODO: Start instance if start this application
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);  // less or equal setInterval value
}

void AppBleScanner::drawUpdate() {

    _resultList.drawUpdate();

    if (_hasDraw) {
        return;
    }

    drawScanInfo();
    _hasDraw = true;
}

void AppBleScanner::reset() {
    _hasDraw = false;
}

void AppBleScanner::setButton1() {
    _resultList.setButton1();
}

void AppBleScanner::drawScanInfo() {
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorOn, _tft->C_BLACK);

    int countFindings = _resultList.GetCountFindings();

    int posX = 40;
    int posY = 45;
    _tft->setCursor(posX, posY);
    _tft->print("Bluetooth Found: ");
    char buffer[12];
    sprintf(buffer, "%d", countFindings);
    _tft->print(buffer);
}

void AppBleScanner::scan() {
    int posX = 80;
    int posY = 25;
    _tft->fillScreen(_tft->C_BLACK);
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorOn, _tft->C_BLACK);

    _tft->setCursor(posX, posY);
    _tft->print("Scan Start");

    BLEScanResults* foundDevices = pBLEScan->start(scanTime, false);
    int n = foundDevices->getCount();

    _tft->setCursor(posX, posY);
    _tft->print("Scan Done ");

    if (n == 0) {
        _tft->setCursor(posX, posY + 20);
        _tft->print("No Bluetooth");
        return;
    }

    for (int i = 0; i < n; i++) {
        BLEAdvertisedDevice device = foundDevices->getDevice(i);

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

        _resultList.addItem(item);
    }
}


void AppBleScanner::setButton2() {
    _resultList.setButton2();
    scan();
    _hasDraw = false;
}
