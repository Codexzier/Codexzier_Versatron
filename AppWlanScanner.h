//
// Created by codexzier on 25.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWLANSCANNER_H
#define CODEXZIER_VERSATRON_APPWLANSCANNER_H

#include <Arduino.h>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include "WiFi.h"
#include "GC9A01_LTSM.hpp"

class WlanItem {

public:
    std::string SSID_Name;
    std::string RSSI;
    std::string Channel;
    std::string Encryption;
};

class AppWlanScanner {
    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    std::unique_ptr<std::vector<WlanItem*>> _wlanItems;

    bool _hasDraw = false;
    void drawScanInfo();
    void drawScannedWifiNetworks();


public:
    AppWlanScanner()
    : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0){ }

    /**
    * Initialize the ring segment display with the given TFT display and colors.
     * @param tft The GC9A01_LTSM TFT display object.
     * @param colorOn The color to use for segments that are on.
     * @param colorOff The color to use for segments that are off.
     * @param colorText The color to use for text.
     */
    void init(GC9A01_LTSM &tft,
              const uint16_t colorOn,
              const uint16_t colorOff,
              const uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;

        WiFi.STA.begin();
    }

    /**
     * Draw content.
     */
    void drawUpdate();

    /**
     * Set all parameter to default.
     */
    //void reset();

    /**
     * For the 3. Button to left the program.
     * @return Value are true, if the app can be closed.
     */
    bool CanBeClosed();

    void scanWifi();

    void setButton1();
};


#endif //CODEXZIER_VERSATRON_APPWLANSCANNER_H
