//
// Created by johan on 25.05.2026.
//

#include "AppWlanScannerResultList.h"

#include <memory>
#include <vector>
#include "GC9A01_LTSM.hpp"


void AppWlanScannerResultList::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    _tft->fillRect(0, 55, 240, 135, _tft->C_BLACK);
    drawWlanItems();
    _hasDraw = true;
}

void AppWlanScannerResultList::drawWlanItems() {

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
        drawWlanItem(posX, posY, i, wlanItemIndex);
        hasDrawItems = true;
    }

    if (!hasDrawItems) {
        _tft->drawRoundRect(posX, posY, 190, 30, 5, _tft->C_RED);
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->setCursor(posX + 4, posY + 4);
        _tft->print("No other Wi-Fi");
        _tft->setCursor(posX + 4, posY + 19);
        _tft->print("networks found.");
    }
}

void AppWlanScannerResultList::drawWlanItem(int x, int y, int index, int itemIndex) {

    WlanItem* item = (*_items)[itemIndex];
    int posY = y + 30 * index;
    _tft->drawRoundRect(x, posY, 190, 30, 5, _colorOff);

    int textPosX = x + 4;
    int textPosY = posY + 4;
    _tft->setCursor(textPosX, textPosY);
    std::string ssid = item->SSID_Name.substr(0, 20);
    _tft->print(ssid.c_str());

    _tft->setTextColor(_colorOff, _tft->C_BLACK);
    _tft->setCursor(textPosX, textPosY + 15);
    _tft->print("RSSI:");
    _tft->setTextColor(_colorOn, _tft->C_BLACK);
    _tft->setCursor(textPosX + 38, textPosY + 15);
    _tft->print(item->RSSI.c_str());

    _tft->setTextColor(_colorOff, _tft->C_BLACK);
    _tft->setCursor(textPosX + 65, textPosY + 15);
    _tft->print("Ch:");
    _tft->setTextColor(_colorOn, _tft->C_BLACK);
    _tft->setCursor(textPosX + 87, textPosY + 15);
    _tft->print(item->Channel.c_str());

    _tft->setTextColor(_colorOff, _tft->C_BLACK);
    _tft->setCursor(textPosX + 105, textPosY + 15);
    _tft->print("Enc:");
    _tft->setTextColor(_colorOn, _tft->C_BLACK);
    _tft->setCursor(textPosX + 136, textPosY + 15);
    _tft->print(item->Encryption.c_str());
}

void AppWlanScannerResultList::addWlanItem(WlanItem *item) {
    if (!_items) {
        _items = std::make_unique<std::vector<WlanItem*>>();
    }

    _items->push_back(item);

    _pageCount = static_cast<int>(_items->size()) / _itemsPerPage;
}

void AppWlanScannerResultList::clearWlanItems() {
    _items.reset(); // TODO: ggf umstellen auf clear()
    _page = 0;
    _pageCount = 0;
    _hasDraw = false;
}


void AppWlanScannerResultList::NextPage() {

    _hasDraw = false;

    if (_page < _pageCount) {
        _page++;
        return;
    }

    _page = 0;
}