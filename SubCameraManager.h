//
// Created by codexzier on 23.06.26.
//

#pragma once

#ifndef CODEXZIER_VERSATRON_SUBCAMERAMANAGER_H
#define CODEXZIER_VERSATRON_SUBCAMERAMANAGER_H

#include <Arduino.h>

#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM

class CameraRecordResult {
public:
    bool Success;
    uint8_t* Buffer;
    uint32_t Length;
};

class SubCameraManager {

    bool _camera_sign = false;          // Check camera status

public:
    void init();

    CameraRecordResult getPicture();
    bool IsCameraReady() const { return _camera_sign; }
};


#endif //CODEXZIER_VERSATRON_SUBCAMERAMANAGER_H
