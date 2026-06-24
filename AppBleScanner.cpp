//
// Created by johan on 26.05.2026.
//

#include "AppBleScanner.h"

void AppBleScanner::initExtend() {

    _resultList.init(*_tft, _colorOn, _colorOff, _colorText);

    /*
    // TODO: Start instance if start this application
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);  // less or equal setInterval value
    */

    _applicationName = "BLE Scanner";
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
    _tft->clearBuffer(_tft->C_BLACK);
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
    _tft->writeBuffer();

/*
    BLEScanResults* foundDevices = pBLEScan->start(scanTime, false);
    int n = foundDevices->getCount();
    */
    BleScanResult scanResult = _bleManager->scan();

    _tft->setCursor(posX, posY);
    _tft->print("Scan Done ");
    _tft->writeBuffer();

    _tft->setCursor(posX, posY + 20);
    if (scanResult.CountDevice == 0) {
        _tft->print("No Bluetooth");
        _tft->writeBuffer();
        return;
    }

    _tft->setCursor(10, 100);
    for (int i = 0; i < scanResult.CountDevice; i++) {
        /*
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

        item->Rssi = device.getRSSI();
*/
        BleItem* item =_bleManager->getBleItem(i);
        _resultList.addItem(item);

        _tft->drawFastHLine(50, 118, i, _colorOn);
        _tft->drawFastHLine(50, 119, i, _colorOn);
        _tft->drawFastHLine(50, 120, i, _colorOn);
        _tft->writeBuffer();
    }
}


void AppBleScanner::setButton2() {
    _resultList.setButton2();
    scan();
    _hasDraw = false;
}
