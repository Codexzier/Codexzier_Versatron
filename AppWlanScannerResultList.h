//
// Created by johan on 25.05.2026.
//

#ifndef CODEXZIER_VERSATRON_APPWLANSCANNERRESULTLIST_H
#define CODEXZIER_VERSATRON_APPWLANSCANNERRESULTLIST_H

#include <Arduino.h>
#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include "GC9A01_LTSM.hpp"


class WlanItem {

public:
    std::string SSID_Name;
    std::string RSSI;
    std::string Channel;
    std::string Encryption;
};

class AppWlanScannerResultList {
    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    std::unique_ptr<std::vector<WlanItem*>> _wlanItems;

    int _page = 0;
    int _pageCount = 0;
    // Anzahl pro Seite
    const int _itemsPerPage = 4;
    void drawWlanItems();
    bool _hasDraw = false;
    void drawWlanItem(int x, int y, int index, int wlanItemIndex);

public:
    AppWlanScannerResultList()
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
    }

    void drawUpdate();
    void addWlanItem(WlanItem* item);
    void clearWlanItems();
    void NextPage();
    int GetCountFindings() {
        return _wlanItems->size();
    }
};


#endif //CODEXZIER_VERSATRON_APPWLANSCANNERRESULTLIST_H
