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

    // TODO: Für die Instanze muss ein Aktiv Flag sein.
    // for (IDrawable* drawable : _drawables) {
    //
    //     if (_drawContent == Menu) {
    //         drawable->drawUpdate();
    //         if (drawable->CanBeClosed()) {
    //             showMenuAppUi();
    //             return;
    //         }
    //     }
    // }
    
    switch (_drawContent) {
        case Menu: {
            _menu.drawUpdate();
            break;
        }
        case Workout: {
            _appWorkout.drawUpdate();

            if (_appWorkout.CanBeClosed()) {
                showMenuAppUi();
            }
            break;
        }
        case Torch: {
            _appTorch.drawUpdate();

            if (_appTorch.CanBeClosed()) {
                showMenuAppUi();
            }
            break;
        }
        case ScanWiFi: {
            _appScnWiFi.drawUpdate();

            if (_appScnWiFi.CanBeClosed()) {
                showMenuAppUi();
            }
            break;
        }
        case ScanBle: {
            _appScnBle.drawUpdate();
            break;
        }
        case PictureViewer: {
            _appPictureViewer.drawUpdate();
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
    _appTorch.reset();
    _appScnWiFi.reset();
    _appScnBle.reset();
}

void Codexzier_Versatron::setValue1(int16_t value) {
    switch (_drawContent) {
        case Menu: {
            _menu.setValue1(value);
            break;
        }
        case Workout: {
            _appWorkout.setValue1(value);
            break;
        }
        case Torch: {
            _appTorch.setValue1(value);
            break;
        }
        case ScanWiFi: {
            break;
        }
        case ScanBle: {
            break;
        }
        case PictureViewer: {
            break;
        }
    }
}

void Codexzier_Versatron::setValue2(int16_t value) {
    switch (_drawContent) {
        case Menu: {
            _menu.setValue2(value);
            break;
        }
        case Workout: {
            break;
        }
        case Torch: {

            break;
        }
        case ScanWiFi: {
            break;
        }
        case ScanBle: {
            break;
        }
        case PictureViewer: {
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
        case Torch: {
            _appTorch.setButton1();
            break;
        }
        case ScanWiFi: {
            _appScnWiFi.setButton1();
            break;
        }
        case ScanBle: {
            _appScnBle.setButton1();
            break;
        }
        case PictureViewer: {
            break;
        }
    }
}

void Codexzier_Versatron::setButton2() {
    switch (_drawContent) {
        case Menu: {
            showApp(static_cast<DrawContent>(_menu.getMenuSelectIndex() + 1));
            break;
        }
        case Workout: {
            _appWorkout.setButton2();
            break;
        }
        case Torch: {
            _appTorch.setButton2();
            break;
        }
        case ScanWiFi: {
            _appScnWiFi.setButton2();
            break;
        }
        case ScanBle: {
            _appScnBle.setButton2();
            break;
        }
        case PictureViewer: {
            break;
        }
    }
}

void Codexzier_Versatron::setButton3() {

    showMenuAppUi();
}
