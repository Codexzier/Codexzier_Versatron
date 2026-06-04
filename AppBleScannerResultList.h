//
// Created by johan on 26.05.2026.
//

#ifndef CODEXZIER_VERSATRON_APPBLESCANNERRESULTLIST_H
#define CODEXZIER_VERSATRON_APPBLESCANNERRESULTLIST_H

#include <Arduino.h>
#include <memory>
#include <string>
#include <vector>

#include "BaseDrawable.h"


class BleItem {

public:
    std::string Name;
    std::string Address;
    std::string DevUUID;
    bool HasDevUUID;

    std::string ManufacturerData;
    bool HasManufacturerData;
};

class AppBleScannerResultList : public BaseDrawable  {

    std::unique_ptr<std::vector<BleItem*>> _items;

    int _page = 0;
    int _pageCount = 0;

    const int _itemsPerPage = 4;

    void drawItems();
    bool _hasDraw = false;
    void drawItem(int x, int y, int index, int itemIndex);

    public:

    void initExtend() override {}
    void drawUpdate() override;
    void setButton1() override;
    void setButton2() override;
    void setButton3() override { _canBeClosed = true; }
    void setValue1(int16_t value) override {}
    void setValue2(int16_t value) override {}
    void reset() override {}

    void addItem(BleItem* item);
    int GetCountFindings() const {

        if (!_items) {
            return 0;
        }

        return _items->size();
    }
};

#endif //CODEXZIER_VERSATRON_APPBLESCANNERRESULTLIST_H
