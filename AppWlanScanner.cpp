//
// Created by codexzier on 25.05.26.
//

#include "AppWlanScanner.h"

#include <algorithm>
#include <Arduino.h>
#include "WiFi.h"
#include "GC9A01_LTSM.hpp"

void AppWlanScanner::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    drawScanInfo();
    drawScannedWifiNetworks();

    _hasDraw = true;
}

bool AppWlanScanner::CanBeClosed() {
    return false;
}

void AppWlanScanner::setButton1() {
    scanWifi();

    _hasDraw = false;
}

void AppWlanScanner::drawScanInfo() {
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorOn, _tft->C_BLACK);

    int countFindings = static_cast<int>(_wlanItems->size());

    int posX = 50;
    int posY = 25;
    _tft->setCursor(posX, posY);
    _tft->print("WLAN Found: ");
    char buffer[12];
    sprintf(buffer, "%d", countFindings);
    _tft->setCursor(posX + 120, posY);
    _tft->print(buffer);
}

void AppWlanScanner::scanWifi() {

    int posX = 50;
    int posY = 25;
    _tft->fillScreen(_tft->C_BLACK);
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorOn, _tft->C_BLACK);

    _tft->setCursor(posX, posY);
    _tft->print("Scan Start");
    int n = WiFi.scanNetworks();
    _tft->setCursor(posX, posY);
    _tft->print("Scan Done ");

    if (n == 0) {
        _tft->setCursor(posX, posY + 20);
        _tft->print("No WiFi Network");
        return;
    }

    char buffer[12];
    for (int i = 0; i < n; i++) {
        Serial.print("Set WiFI Item: ");
        Serial.println(i, DEC);

        WlanItem* newItem = new WlanItem;
        newItem->SSID_Name = WiFi.SSID(i).c_str();
        Serial.println(newItem->SSID_Name.c_str());
        int rssi = (int)WiFi.RSSI(i);
        sprintf(buffer, "%d", rssi);
        newItem->RSSI = buffer;
        Serial.println(newItem->RSSI.c_str());
        int channel = (int)WiFi.channel(i);
        sprintf(buffer, "%d", channel);
        newItem->Channel = buffer;
        Serial.println(newItem->Channel.c_str());


        switch (WiFi.encryptionType(i)) {
            case WIFI_AUTH_OPEN:            newItem->Encryption = "open"; break;
            case WIFI_AUTH_WEP:             newItem->Encryption = "WEP"; break;
            case WIFI_AUTH_WPA_PSK:         newItem->Encryption = "WPA"; break;
            case WIFI_AUTH_WPA2_PSK:        newItem->Encryption = "WPA2"; break;
            case WIFI_AUTH_WPA_WPA2_PSK:    newItem->Encryption = "WPA+WPA2"; break;
            case WIFI_AUTH_WPA2_ENTERPRISE: newItem->Encryption = "WPA2-EAP"; break;
            case WIFI_AUTH_WPA3_PSK:        newItem->Encryption = "WPA3"; break;
            case WIFI_AUTH_WPA2_WPA3_PSK:   newItem->Encryption = "WPA2+WPA3"; break;
            case WIFI_AUTH_WAPI_PSK:        newItem->Encryption = "WAPI"; break;
            default:                        newItem->Encryption = "unknown";
        }
        Serial.println(newItem->Encryption.c_str());

        Serial.println("Try to push");
        if (!_wlanItems) {
            _wlanItems = std::make_unique<std::vector<WlanItem*>>();
        }
        _wlanItems->push_back(newItem);
        Serial.print("has push");
        Serial.println(i, DEC);
    }
}

void AppWlanScanner::drawScannedWifiNetworks() {
    if (!_wlanItems) {

        return;
    }

    int posX = 10;
    int posY = 60;

    int countFindings = static_cast<int>(_wlanItems->size());
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorOn, _tft->C_BLACK);

    for (int i = 0; i < countFindings; i++) {

        if ((posY + (i * 15)) > 190) {
            return;
        }

        WlanItem* item = (*_wlanItems)[i];
        _tft->setCursor(posX, posY + (15 * i));
        std::string ssid = item->SSID_Name.substr(0, 14);
        _tft->print(ssid.c_str());

        _tft->setCursor(posX + 130, posY + (15 * i));
        _tft->print(item->RSSI.c_str());

        _tft->setCursor(posX + 170, posY + (15 * i));
        _tft->print(item->Channel.c_str());
        _tft->setCursor(posX + 190, posY + (15 * i));
        _tft->print(item->Encryption.c_str());
    }

}
