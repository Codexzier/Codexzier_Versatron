//
// Created by codexzier on 25.05.26.
//

#include "AppCameraRun.h"

#include "esp_camera.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "camera_pins.h"
#include "fonts_LTSM/FontArialBold_LTSM.hpp"

// Save pictures to SD card
void AppCameraRun::photo_save(const char * fileName) {
    // Take a photo
    camera_fb_t *fb = esp_camera_fb_get();

    _tft->setFont(FontArialBold);
    _tft->setCursor(100, 100);

    if (!fb) {
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to get camera frame buffer");
        return;
    }
    // Save photo to file
    writeFile(SD, fileName, fb->buf, fb->len);

    // Release image buffer
    esp_camera_fb_return(fb);

    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Photo saved to file");
}

// SD card write file
void AppCameraRun::writeFile(FS &fs, const char * path, uint8_t * data, size_t len){

    _tft->setFont(FontArialBold);
    _tft->setCursor(50, 50);
    Serial.printf("Writing file: %s\n", path);
    _tft->print("writing file");

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Failed to open file for writing");
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.write(data, len) == len){
        Serial.println("File written");
        _tft->print("File written");
    } else {
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        Serial.println("Write failed");
        _tft->print("write failed");
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

    _tft->setFont(FontArialBold);
    _tft->setCursor(100, 100);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("init camera");
    Serial.println("init camera");

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Camera init faild");
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    _camera_sign = true; // Camera initialization check passes

    // Initialize SD card
    if(!SD.begin(21)){
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("Card Mount Failed");
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    _tft->print("read card type");
    Serial.println("read card type");
    // Determine if the type of SD card is available
    if(cardType == CARD_NONE){
        _tft->setTextColor(_tft->C_RED, _tft->C_BLACK);
        _tft->print("No SD card attached");
        Serial.println("No SD card attached");
        return;
    }

    _tft->print("SD Card Type: ");
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        _tft->print("MMC");
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        _tft->print("SDSC");
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        _tft->print("SDHC");
        Serial.println("SDHC");
    } else {
        _tft->print("UNKNOWN");
        Serial.println("UNKNOWN");
    }

    _sd_sign = true; // sd initialization check passes

    _tft->print("Ready");
    Serial.println("Ready.");
}

void AppCameraRun::drawUpdate() {

}

void AppCameraRun::setButton1() {

}

void AppCameraRun::setButton2() {
    char filename[32];
    sprintf(filename, "/image%d.jpg", _imageCount);
    photo_save(filename);

    _tft->setFont(FontArialBold);
    _tft->setCursor(100, 100);
    _tft->setTextColor(_colorText, _tft->C_BLACK);
    _tft->print("Saved picture");

    Serial.printf("Saved picture：%s\n", filename);
    _imageCount++;
}


