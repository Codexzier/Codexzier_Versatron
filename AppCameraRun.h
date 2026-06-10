//
// Created by codexzier on 25.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPCAMERARUN_H
#define CODEXZIER_VERSATRON_APPCAMERARUN_H
#include "BaseDrawable.h"


class AppCameraRun : public BaseDrawable {

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
