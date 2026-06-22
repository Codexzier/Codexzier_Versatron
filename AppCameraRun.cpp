//
// Created by codexzier on 25.05.26.
//

#include "AppCameraRun.h"

#include "esp_camera.h"
#include "camera_pins.h"
#include <string>
#include <memory>

#include "GC9A01_LTSM.hpp"
#include "display16_graphics_LTSM.hpp"


// Save pictures to SD card
void AppCameraRun::photo_save(const char * fileName) {

    // Take a photo
    // das erste bild aufrufen und verwerfen.
    camera_fb_t *fb_old = esp_camera_fb_get();
    esp_camera_fb_return(fb_old);

    // camera frame buffer
    camera_fb_t *fb = esp_camera_fb_get();

    _tft->setFont(FontDefault);

    if (!fb) {
        _tft->setCursor(_posX - 20, _posY - 100);
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to get camera frame buffer");
        Serial.println("Failed to get camera frame buffer");
        delay(1000);
        return;
    }

    // Save photo to file
    uint8_t* picture = fb->buf;
    const uint32_t len = fb->len;
    _fileManager->writeFile(fileName, picture, len);

    char buffer[10];
    sprintf(buffer, "%02d", len);
    Serial.print("Buffer Länge: "); Serial.println(len, DEC);

    //_tft->TFTsetRotation(2);
    //_tft->drawSpriteData(0, 0, buf, 240, 240, _tft->C_BLUE, false);
    drawPicture(picture);

    // Release image buffer
    esp_camera_fb_return(fb);

    _tft->setCursor(30, 170);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Photo saved");
    Serial.println("Photo saved to file");
}

void AppCameraRun::drawPicture(const uint8_t* bitmap) {

    // draw frame
    _tft->drawRoundRect(120, 60, 120, 120, 4, _colorOn);

    const uint8_t* bitmapIter = bitmap;
    uint16_t colour;
    for (int16_t y = 239; y >= 0; y--) {

        for (int16_t x = 0; x < 240; x++) {

            uint8_t hi = pgm_read_byte(bitmapIter);       // high byte
            uint8_t lo = pgm_read_byte(bitmapIter + 1);   // low byte
            colour = (static_cast<uint16_t>(hi) << 8) | static_cast<uint16_t>(lo);
            bitmapIter += 2;

            _tft->drawPixel(120 + (x / 2), 60 + y / 2, colour);
        }
    }

    _tft->drawRoundRect(120, 60, 120, 120, 4, _colorOn);
}

/*
void AppCameraRun::drawLastPicture() {

    constexpr int16_t posX = 30;
    constexpr int16_t posY = 45;
    _tft->setFont(FontDefault);
    _tft->setCursor(posX, posY);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print(_lastFilename.c_str());
    Serial.printf("Reading file: %s\n", _lastFilename.c_str());

    std::string fullpath = _lastFilename; // "/" +
    Serial.printf("fullpath file: %s\n", fullpath.c_str());
    _tft->setCursor(posX, posY + 10);
    File file = SD.open(fullpath.c_str());
    if(!file){
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to open");
        _tft->setCursor(posX, posY + 20);
        _tft->print("file for reading");
        Serial.println("Failed to open file for reading");
        delay(1000);
        return;
    }

    _tft->print("Read from file: ");
    Serial.print("Read from file: ");

    // -------------------
    // Header

    // Offset
    // springe zu bild offset header information
    const uint32_t indexPictureStart = GetHeaderInformation(file, 10);

    // width and hight
    const uint32_t picWidth = GetHeaderInformation(file, 18);
    const uint32_t picHeight = GetHeaderInformation(file, 22);

    Serial.print("Offset: "); Serial.print(indexPictureStart, DEC);
    Serial.print(", Breite: "); Serial.print(picWidth, DEC);
    Serial.print(", Höhe: "); Serial.println(picHeight, DEC);

    Serial.println("Lese Bilddatei aus: ");
    file.seek(0);
    uint32_t countPixel = 0;
    for (int16_t y = 239; y >= 0; y--) {

        if (!file.available()) {
            continue;
        }

        for (int16_t x = 0; x < 240; x++) {

            const uint16_t pixelFarbe = GetNextPixelColorValue(file);

            //Serial.print(pixelFarbe, DEC);
            _tft->drawPixel(x, y, pixelFarbe);
            countPixel++;
        }
        //Serial.println("");
    }
    file.close();

    Serial.print("Anzahl Pixel ausgelesen: ");
    Serial.println(countPixel, DEC);
}
*/

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

    const int fileCount = 0; //static_cast<int>(_filenames->size());
    Serial.print("Count pictures: ");
    Serial.println(fileCount, DEC);

    if (fileCount == 0) {
        _tft->setCursor(posX - 20, posY + 60);
        _tft->print("Pictures: 0");
        return;
    }

    /*
    int lastPictures = 3 ;
    if (fileCount < 3) {
        lastPictures = fileCount;
    }

    int indexPos = 1;
    for (int index = fileCount - lastPictures; index < fileCount; index++) {
        std::string filename = (*_filenames)[index];
        _tft->setCursor(posX, posY + indexPos * 10);
        _tft->print(filename.c_str());
        indexPos++;
    }

    _tft->drawFastHLine(0, posY + 50, 120, _colorOn);
    _tft->setCursor(posX - 20, posY + 60);
    _tft->print("Pictures: ");

    sprintf(buffer, "%02d", fileCount);
    _tft->print(buffer);
    */
    char buffer[10];

    _tft->setCursor(posX - 20, posY + 80);
    _tft->print("used: ");
    int cardsizeMb = _fileManager->GetCardSizeMb(); //SD.usedBytes() / 1024 / 1024;
    sprintf(buffer, "%02d", cardsizeMb);
    _tft->print(buffer); _tft->print("MB");
}

void AppCameraRun::initExtend() {

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;

    // data pins
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    // control gpio
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;

    //config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    //config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;

    // not connected
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;

    // Bitmap Einstellung
    config.pixel_format = PIXFORMAT_RGB565;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    config.frame_size = FRAMESIZE_240X240;
//#if CONFIG_IDF_TARGET_ESP32S3
      //  config.fb_count = 2;
//#endif
    //}

    Serial.println("init camera");

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        delay(1000);
        return;
    }

    // Camera initialization check passes
    _camera_sign = true;



    // sd initialization check passes
    _sd_sign = true;
    Serial.println("Ready.");
}

void AppCameraRun::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    Serial.println("refresh tft content");

    Serial.println("read files");
    //readFiles();

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

    //_tft->fillScreen(_tft->C_BLACK);
    _tft->drawRoundRect(120, 60, 120, 120, 4, _tft->C_YELLOW);
    _tft->writeBuffer();
    _tft->clearBuffer();

    _tft->setFont(FontDefault);
    _tft->setCursor(10, 150);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Save picture: ");

    _imageCount++;
    char filename[32];
    sprintf(filename, "/image%d.bmp", _imageCount);
    _tft->setCursor(40, 170);
    _tft->print(filename);
    //_lastFilename = filename;
    photo_save(filename);

    char buffer[10];
    sprintf(buffer, "%02d", _imageCount);
    _tft->setCursor(60, 160);
    _tft->print(buffer);

    Serial.printf("Saved picture：%s\n", filename);

    _hasDraw = false;
}


