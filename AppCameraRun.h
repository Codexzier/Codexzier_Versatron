//
// Created by codexzier on 25.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPCAMERARUN_H
#define CODEXZIER_VERSATRON_APPCAMERARUN_H

#include "BaseDrawable.h"
#include "FS.h"

#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM


class AppCameraRun : public BaseDrawable {

    int _imageCount = 1;                // File Counter
    bool _camera_sign = false;          // Check camera status
    bool _sd_sign = false;              // Check sd status

    void photo_save(const char * fileName);
    void writeFile(FS &fs, const char * path, uint8_t * data, size_t len);

public:

    void initExtend() override;
    void drawUpdate() override;
    void setButton1() override;
    void setButton2() override;
    void setButton3() override { _canBeClosed = true; }
    void setValue1(int16_t value) override {}
    void setValue2(int16_t value) override {}
    void reset() override {}
};


#endif //CODEXZIER_VERSATRON_APPCAMERARUN_H
