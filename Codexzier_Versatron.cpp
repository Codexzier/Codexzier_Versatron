//
// Created by codexzier on 26.04.26.
//

#include "Codexzier_Versatron.h"
#include "MenuArea.h"


// ################################################################
// Public
// ================================================================
// render update content
void Codexzier_Versatron::drawUpdate()
{
    switch (_drawContent) {
        case Menu: {
            _menu.drawUpdate();
            break;
        }
        case Workout: {
            break;
        }
    }
}

// ================================================================
// menu
void Codexzier_Versatron::showMenuAppUi(){
    _tft->fillScreen(_tft->C_BLACK);
    _menu.resetInitializedDrawMenu();
}
void Codexzier_Versatron::addMenuItem(const MenuItem& item){
    _menu.addItem(item);
}

void Codexzier_Versatron::nextMenuSelect() {
    _menu.nextMenuSelect();
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



// ================================================================
// private