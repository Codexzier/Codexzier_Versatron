//
// Created by codexzier on 25.05.26.
//

#include "AppCameraRun.h"
#include <string>
#include <memory>

#include "GC9A01_LTSM.hpp"
#include "display16_graphics_LTSM.hpp"

void AppCameraRun::photo_save(const char * fileName) {

    const CameraRecordResult result = _cameraManager->getPicture();

    if (!result.Success) {
        _tft->setCursor(_posX - 20, _posY - 100);
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to get camera frame buffer");
        return;
    }

    _fileManager->writeFile(fileName, result.Buffer, result.Length);

    char buffer[10];
    sprintf(buffer, "%02d", result.Length);
    Serial.print("Buffer Länge: "); Serial.println(result.Length, DEC);

    drawPicture(result.Buffer);

    // Release image buffer
    //esp_camera_fb_return(fb);

    _tft->setCursor(30, 170);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Photo saved");
    Serial.println("Photo saved to file");
}

void AppCameraRun::drawPicture(const uint8_t* bitmap) {

    // draw frame
    _tft->drawRoundRect(120, 60, 120, 120, 4, _colorOn);

    // draw recorded picture
    const uint8_t* bitmapIter = bitmap;
    uint16_t colour;
    for (int16_t y = 239; y >= 0; y--) {
    //for (int16_t y = 119; y >= 0; y--) {

        for (int16_t x = 0; x < 240; x++) {
        //for (int16_t x = 0; x < 120; x++) {

            uint8_t hi = pgm_read_byte(bitmapIter);       // high byte
            uint8_t lo = pgm_read_byte(bitmapIter + 1);   // low byte
            colour = (static_cast<uint16_t>(hi) << 8) | static_cast<uint16_t>(lo);
            bitmapIter += 2;

            _tft->drawPixel(120 + (x / 2), 60 + (y / 2), colour);
        }
    }

    _tft->drawRoundRect(120, 60, 120, 120, 4, _colorOn);
}

uint32_t AppCameraRun::GetHeaderInformation(File &file, uint32_t position) {

    file.seek(position);
    uint8_t b0 = file.read();
    uint8_t b1 = file.read();
    uint8_t b2 = file.read();
    uint8_t b3 = file.read();

    return  b0 | b1 << 8 | b2 << 16 | b3 << 24;
}

uint16_t AppCameraRun::GetNextPixelColorValue(File &file) {


    const uint8_t highByte = file.read(); // Zweites Byte (hochwertig)
    const uint8_t lowByte = file.read();  // Erstes Byte (niederwertig)

    const uint16_t color = highByte << 8 | lowByte;

    return color;
}

void AppCameraRun::drawText(){

    constexpr int16_t posX = 30;
    constexpr int16_t posY = 45;
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    const int fileCount = _fileManager->GetCountPictures();
    Serial.print("Count pictures: ");
    Serial.println(fileCount, DEC);

    if (fileCount == 0) {
        _tft->setCursor(posX - 20, posY + 60);
        _tft->print("Pictures: 0");
        return;
    }

    char buffer[10];

    _tft->setCursor(posX - 20, posY + 80);
    _tft->print("used: ");
    int cardsizeMb = _fileManager->GetCardSizeMb(); //SD.usedBytes() / 1024 / 1024;
    sprintf(buffer, "%02d", cardsizeMb);
    _tft->print(buffer); _tft->print("MB");
}

void AppCameraRun::initExtend() {

    _applicationName = "Camera";
}

void AppCameraRun::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    Serial.println("refresh tft content");

    Serial.println("read files");

    Serial.println("draw last frame");
    //drawLastPicture();

    _tft->drawCircle(120, 120, 119, _colorOn);
    _tft->drawCircle(120, 120, 118, _colorOff);
    _tft->drawCircle(120, 120, 117, _colorOff);

    Serial.println("draw text");
    drawText();

    _hasDraw = true;
}

void AppCameraRun::setButton1() {

}

void AppCameraRun::setButton2() {

    if (!_cameraManager->IsCameraReady()) {

        _tft->setFont(FontDefault);
        _tft->setCursor(10, 150);
        _tft->setTextColor(_colorText, _tft->C_BLACK);
        _tft->print("Camera not ready");
        return;
    }

    _tft->drawRoundRect(120, 60, 120, 120, 4, _tft->C_YELLOW);
    _tft->writeBuffer();
    _tft->clearBuffer();

    _tft->setFont(FontDefault);
    _tft->setCursor(10, 150);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Save picture: ");

    if (_imageCount == 0) {
        _imageCount = _fileManager->GetCountPictures();
    }
    _imageCount++;
    char filename[32];
    sprintf(filename, "/image%d.bmp", _imageCount);
    _tft->setCursor(40, 170);
    _tft->print(filename);

    photo_save(filename);

    char buffer[10];
    sprintf(buffer, "%02d", _imageCount);
    _tft->setCursor(60, 160);
    _tft->print(buffer);

    Serial.printf("Saved picture：%s\n", filename);

    _hasDraw = false;
}


