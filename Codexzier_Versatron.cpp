//
// Created by codexzier on 26.04.26.
//

#include "Codexzier_Versatron.h"
#include "AppMenu.h"
#include "AppWorkout.h"
#include "RingSegmentDisplay.h"
#include <math.h>
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels
#include "fonts_LTSM/FontPico_LTSM.hpp"         // 8x12 pixels
#include "fonts_LTSM/FontSinclairS_LTSM.hpp"    // 8x8 pixels


void Codexzier_Versatron::drawMenuAppUi()
{
    _tft->fillScreen(_tft->C_BLACK);
    _appMenu.resetInitializedDrawMenu();
    _appMenu.drawMenu();
}
void Codexzier_Versatron::addMenuItem(const MenuItem& item)
{
    _appMenu.addItem(item);
}

void Codexzier_Versatron::drawWorkoutAppUi()
{
    _tft->fillScreen(_tft->C_BLACK);
}

void Codexzier_Versatron::drawWorkoutAppNextOption() {
    _tft->fillScreen(_tft->C_BLACK);
    _appWorkout.setNextOption();
}

void Codexzier_Versatron::setWorkoutAppRun() {
    _tft->fillScreen(_tft->C_BLACK);
    _appWorkout.setOptionRun();
}

void Codexzier_Versatron::drawUpdate()
{
    _appWorkout.drawUpdate();
}