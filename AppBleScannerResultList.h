//
// Created by johan on 26.05.2026.
//

#ifndef CODEXZIER_VERSATRON_APPBLESCANNERRESULTLIST_H
#define CODEXZIER_VERSATRON_APPBLESCANNERRESULTLIST_H

#include <Arduino.h>
#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include "GC9A01_LTSM.hpp"


class BleItem {

public:
    std::string Name;
    std::string Address;
    std::string DevUUID;
    bool HasDevUUID;

    std::string ManufacturerData;
    bool HasManufacturerData;
};

class AppBleScannerResultList {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    std::unique_ptr<std::vector<BleItem*>> _items;

    int _page = 0;
    int _pageCount = 0;

    const int _itemsPerPage = 4;

    void drawItems();
    bool _hasDraw = false;
    void drawItem(int x, int y, int index, int itemIndex);

    public:
    AppBleScannerResultList()
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
    void addItem(BleItem* item);
    void clearItems();
    void NextPage();
    int GetCountFindings() {

        if (!_items) {
            return 0;
        }

        return _items->size();
    }
};


#endif //CODEXZIER_VERSATRON_APPBLESCANNERRESULTLIST_H
