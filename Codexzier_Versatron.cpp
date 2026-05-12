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
            _appWorkout.drawUpdate();
            break;
        }
    }
}

// ================================================================
// menu
void Codexzier_Versatron::showMenuAppUi(){
    _tft->fillScreen(_tft->C_BLACK);
    _drawContent = Menu;
    _menu.resetInitializedDrawMenu();
}
void Codexzier_Versatron::addMenuItem(const MenuItem& item){
    _menu.addItem(item);
}


// ================================================================
// app start
void Codexzier_Versatron::showApp(DrawContent content) {

    _tft->fillScreen(_tft->C_BLACK);
    _drawContent = content;
    _appWorkout.reset();
}

void Codexzier_Versatron::setValue1(int16_t value) {
    switch (_drawContent) {
        case Menu: {
            break;
        }
        case Workout: {
            _appWorkout.setValue1(value);
            break;
        }
    }
}

void Codexzier_Versatron::setButton1() {
    switch (_drawContent) {
        case Menu: {
            _menu.nextMenuSelect();
            break;
        }
        case Workout: {
            _appWorkout.setButton1();
            break;
        }
    }
}

void Codexzier_Versatron::setButton2() {
    switch (_drawContent) {
        case Menu: {
            break;
        }
        case Workout: {
            _appWorkout.setButton2();
            break;
        }
    }
}