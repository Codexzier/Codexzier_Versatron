//
// Created by johan on 26.05.2026.
//

#include "AppBleScannerResultList.h"

#include <memory>
#include <vector>
#include "GC9A01_LTSM.hpp"


void AppBleScannerResultList::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    _tft->fillRect(0, 55, 240, 135, _tft->C_BLACK);
    drawItems();
    _hasDraw = true;

}

void AppBleScannerResultList::drawItems() {
    if (!_items) {
        return;
    }

    int posX = 25;
    int posY = 60;

    int countFindings = static_cast<int>(_items->size());
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorOn, _tft->C_BLACK);

    _tft->setCursor(70, 190);
    _tft->print("Page: ");
    char buffer[12];
    sprintf(buffer, "%d", (_page + 1));
    _tft->print(buffer);
    _tft->print(" / ");
    sprintf(buffer, "%d", (_pageCount + 1));
    _tft->print(buffer);

    bool hasDrawItems = false;
    for (int i = 0; i < _itemsPerPage; i++) {
        int wlanItemIndex = _page * _itemsPerPage + i;
        if (wlanItemIndex >= countFindings) {
            break;
        }
        drawItem(posX, posY, i, wlanItemIndex);
        hasDrawItems = true;
    }

    if (!hasDrawItems) {
        _tft->drawRoundRect(posX, posY, 190, 30, 5, _tft->C_RED);
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->setCursor(posX + 4, posY + 4);
        _tft->print("No other Bluetooth");
        _tft->setCursor(posX + 4, posY + 19);
        _tft->print("networks found.");
    }
}

void AppBleScannerResultList::drawItem(int x, int y, int index, int itemIndex) {
    BleItem* item = (*_items)[itemIndex];
    int posY = y + 30 * index;

    uint16_t roundRectColor = _colorOff;
    if (item->HasDevUUID) {
        roundRectColor = _tft->C_YELLOW;
    }
    if (item->HasManufacturerData) {
        roundRectColor = _tft->C_GREEN;
    }
    _tft->drawRoundRect(x, posY, 190, 30, 5, roundRectColor);

    int textPosX = x + 4;
    int textPosY = posY + 4;
    _tft->setCursor(textPosX, textPosY);
    _tft->print(item->Name.c_str());

    textPosY += 15;
    _tft->setCursor(textPosX, textPosY);
    _tft->print(item->Address.c_str());
}

void AppBleScannerResultList::addItem(BleItem *item) {
    if (!_items) {
        _items = std::make_unique<std::vector<BleItem*>>();
    }

    _items->push_back(item);
    _pageCount = static_cast<int>(_items->size()) / _itemsPerPage;
}

void AppBleScannerResultList::clearItems() {
    _items.reset();
    _pageCount = 0;
    _page = 0;
    _hasDraw = false;
}

void AppBleScannerResultList::NextPage() {
    _hasDraw = false;
    if (_page < _pageCount) {
        _page++;
        return;
    }
    _page = 0;
}
