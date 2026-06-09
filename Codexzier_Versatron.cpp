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
    for (IDrawable* drawable : _drawables) {

        if (!drawable->IsActive()) {
            continue;
        }

        drawable->drawUpdate();

        if (drawable->CanBeClosed()) {
            showMenuAppUi();
            return;
        }
    }
}

// ================================================================
// menu
void Codexzier_Versatron::showMenuAppUi(){
    _tft->fillScreen(_tft->C_BLACK);
    _drawContent = Menu;
    _menu.resetInitializedDrawMenu();

    for (IDrawable* drawable : _drawables) {
        drawable->SetActive(false);
    }
    _menu.SetActive(true);
}
void Codexzier_Versatron::addMenuItem(const MenuItem& item){
    _menu.addItem(item);
}

// ================================================================
// app start
void Codexzier_Versatron::showApp(DrawContent content) {

    _tft->fillScreen(_tft->C_BLACK);
    _drawContent = content;

    for (IDrawable* drawable : _drawables) {
        drawable->reset();
        drawable->SetActive(false);
    }

    switch (_drawContent) {
        case Menu: {
            _menu.SetActive(true);
            break;
        }
        case Workout: {
            _appWorkout.SetActive(true);
            break;
        }
        case Torch: {
            _appTorch.SetActive(true);
            break;
        }
        case ScanWiFi: {
            _appScnWiFi.SetActive(true);
            break;
        }
        case ScanBle: {
            _appScnBle.SetActive(true);
            break;
        }
        case PictureViewer: {
            _appPictureViewer.SetActive(true);
            break;
        }
    }
}

void Codexzier_Versatron::setValue1(int16_t value) {

    for (IDrawable* drawable : _drawables) {
        if (!drawable->IsActive()) {
            continue;
        }
        drawable->setValue1(value);
    }
}

void Codexzier_Versatron::setValue2(int16_t value) {

    for (IDrawable* drawable : _drawables) {
        if (!drawable->IsActive()) {
            continue;
        }
        drawable->setValue2(value);
    }
}

void Codexzier_Versatron::setButton1() {

    for (IDrawable* drawable : _drawables) {
        if (!drawable->IsActive()) {
            continue;
        }
        drawable->setButton1();
    }
}

void Codexzier_Versatron::setButton2() {

    if (_drawContent == Menu) {
        showApp(static_cast<DrawContent>(_menu.getMenuSelectIndex() + 1));
        return;
    }

    for (IDrawable* drawable : _drawables) {
        if (!drawable->IsActive()) {
            continue;
        }
        drawable->setButton2();
    }

    return;
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
