//
// Created by codexzier on 26.04.26.
//

#include "Codexzier_Versatron.h"
#include "MenuArea.h"
#include <string>


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
    _tft->writeBuffer();
}

// ================================================================
// menu
void Codexzier_Versatron::showMenuAppUi(){
    _tft->fillScreen(_tft->C_BLACK);
    _drawContentName = _menu.GetApplicationName();
    _menu.reset();
    _tft->clearBuffer(_tft->C_BLACK);

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
//void Codexzier_Versatron::showApp(DrawContent content) {
void Codexzier_Versatron::showApp(std::string content) {

    _tft->fillScreen(_tft->C_BLACK);
    _drawContentName = content;

    Serial.print("set draw content: ");
    Serial.println(content.c_str());

    for (IDrawable* drawable : _drawables) {
        drawable->reset();
        std::string applicationName = drawable->GetApplicationName();
        Serial.print("Active: "); Serial.print(drawable->IsActive(), DEC);
        Serial.print(", ApplicationName: "); Serial.print(applicationName.c_str());
        drawable->SetActive(applicationName == content);
        Serial.print(" -> Active: "); Serial.println(drawable->IsActive(), DEC);
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

    if (_drawContentName == "Menu") {
        // Um Menu zu überspringen
        const int index = _menu.getMenuSelectIndex() + 1;
        showApp(_drawables[index]->GetApplicationName());
        return;
    }

    for (IDrawable* drawable : _drawables) {
        if (!drawable->IsActive()) {
            continue;
        }
        drawable->setButton2();
    }
}

void Codexzier_Versatron::setButton3() {
    showMenuAppUi();
}
