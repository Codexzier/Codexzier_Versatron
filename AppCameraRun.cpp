//
// Created by codexzier on 25.05.26.
//

#include "AppCameraRun.h"

#include "esp_camera.h"
#include "FS.h"
#include "SD.h"
//#include "SPI.h"
#include "camera_pins.h"
//#include "fonts_LTSM/FontArialBold_LTSM.hpp"
#include <vector>
#include <string>
#include <memory>

// Save pictures to SD card
void AppCameraRun::photo_save(const char * fileName) {
    // Take a photo
    camera_fb_t *fb = esp_camera_fb_get();

    _tft->setFont(FontDefault);

    if (!fb) {
        _tft->setCursor(_posX - 20, _posY - 100);
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to get camera frame buffer");
        return;
    }

    // Save photo to file
    writeFile(SD, fileName, fb->buf, fb->len);

    // Release image buffer
    esp_camera_fb_return(fb);

    _tft->setCursor(_posX - 25, _posY);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Photo saved to file");
}

// SD card write file
void AppCameraRun::writeFile(FS &fs, const char * path, uint8_t * data, size_t len){

    _tft->setFont(FontDefault);
    _tft->setCursor(_posX, _posY - 60);
    _tft->print("writing file");
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to open file for writing");
        Serial.println("Failed to open file for writing");
        return;
    }

    _tft->setCursor(_posX, _posY - 40);
    if(file.write(data, len) == len){
        _tft->print("File written");
        Serial.println("File written");
    } else {
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("write failed");
        Serial.println("Write failed");
    }
    file.close();
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
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;

    // not connected
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_UXGA;
    config.pixel_format = PIXFORMAT_JPEG; // for streaming
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
    //                      for larger pre-allocated frame buffer.
    if(config.pixel_format == PIXFORMAT_JPEG){
        if(psramFound()){
            config.jpeg_quality = 10;
            config.fb_count = 2;
            config.grab_mode = CAMERA_GRAB_LATEST;
        } else {
            // Limit the frame size when PSRAM is not available
            config.frame_size = FRAMESIZE_SVGA;
            config.fb_location = CAMERA_FB_IN_DRAM;
        }
    } else {
        // Best option for face detection/recognition
        config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
        config.fb_count = 2;
#endif
    }

    Serial.println("init camera");

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    // Camera initialization check passes
    _camera_sign = true;

    // Initialize SD card
    if(!SD.begin(21)){

        Serial.println("Card Mount Failed");
        return;
    }

    uint8_t cardType = SD.cardType();
    Serial.println("read card type");

    // Determine if the type of SD card is available
    if(cardType == CARD_NONE){

        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    // sd initialization check passes
    _sd_sign = true;
    Serial.println("Ready.");

    // SD Karte auslesen nach Dateien
    const int16_t posX = 70;
    const int16_t posY = 35;
    _tft->setCursor(posX, posY);

    File root = SD.open("/");
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return;
    }

    if (!_filenames) {
        _filenames = std::make_unique<std::vector<std::string>>();
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());

            _filenames->push_back(file.name());
            _imageCount++;
        }
        file = root.openNextFile();
    }
}

void AppCameraRun::drawUpdate() {

    if (_hasDraw) {
        return;
    }

    constexpr int16_t posX = 30;
    constexpr int16_t posY = 45;
    _tft->setFont(FontDefault);
    _tft->setTextColor(_colorText, _tft->C_BLACK);

    const int fileCount = static_cast<int>(_filenames->size());
    for (int index = 0; index < fileCount; index++) {
        std::string filename = (*_filenames)[index];
        _tft->setCursor(posX, posY + (index * 10));
        _tft->print(filename.c_str());
    }

    _hasDraw = true;
}

void AppCameraRun::setButton1() {

}

void AppCameraRun::setButton2() {

    char filename[32];
    sprintf(filename, "/image%d.jpg", _imageCount);
    photo_save(filename);

    _tft->drawCircle(120, 120, 119, _colorOn);
    _tft->drawCircle(120, 120, 118, _colorOff);
    _tft->drawCircle(120, 120, 117, _colorOff);

    constexpr int16_t posX = 50;
    constexpr int16_t posY = 145;

    _tft->setFont(FontDefault);
    _tft->setCursor(posX, posY);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Saved picture: ");

    char buffer[10];
    sprintf(buffer, "%02d", _imageCount);
    _tft->print(buffer);

    Serial.printf("Saved picture：%s\n", filename);
    _imageCount++;

    _hasDraw = false;
    _tft->fillScreen(_tft->C_BLACK);
}


