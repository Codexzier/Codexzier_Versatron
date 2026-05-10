//
// Created by codexzier on 10.05.26.
//

#include "AppWorkoutSetup.h"

#include <cstdio>

#include "fonts_LTSM/FontArialBold_LTSM.hpp"

void AppWorkoutSetup::drawUpdate() {
    drawOptionSetup();
}

void AppWorkoutSetup::drawOptionSetup() {

    // TODO: Folgende Einstellgungen vornehmen

    if (!_option1SetupHasDraw) {
        _tft->drawCircle(120, 120, 99, _colorOn);

        _tft->setCursor(_startX, _startY);
        _tft->setFont(FontArialBold);
        _tft->setTextColor(_colorText, _tft->C_BLACK);
        _tft->print("Workout");
        _tft->setCursor(_startX, _startY + 20);
        _tft->print("Setup 1");

        _tft->drawFastHLine(_startX, _startY + 45, 140, _colorText);

        _tft->drawFastHLine(_startX, _startY + 100, 140, _colorText);
    }

    // TODO: Wie lange die Ausführung dauert soll
    // TODO: Der Wert in _secondsExecutionMax muss über den Poti gesetzt werden
    drawOption1SetupTextAndTime(_startX, _startY + 50, "Execut", _secondsExecutionMax);

    // TODO: Wie lange die Pause dauert soll
    drawOption1SetupTextAndTime(_startX, _startY + 65, "Break", _secondsBreakMax);

    // TODO: Anzahl der Runden
    drawOption1SetupTextAndTime(_startX, _startY + 80, "Rounds", _roundMax);

    _option1SetupHasDraw = true;
}

void AppWorkoutSetup::drawOption1SetupTextAndTime(int x, int y, const char *text, int value) {

    _tft->setFont(FontArialBold);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    if (!_option1SetupHasDraw) {
        _tft->setCursor(x, y);
        _tft->print(text);
    }

    _tft->setCursor(x + 100, y);
    char buffer[10];
    sprintf(buffer, "%02d", value);
    _tft->print(buffer);
}
