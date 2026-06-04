//
// Created by codexzier on 04.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWORKOUT_H
#define CODEXZIER_VERSATRON_APPWORKOUT_H

#include <Arduino.h>
#include "AppWorkoutRun.h"
#include "GC9A01_LTSM.hpp"
#include "AppWorkoutSetup.h"
#include "BaseDrawable.h"

class AppWorkout : public BaseDrawable {

    int _option = 1;
    bool _optionRun = false;

    // Setup and run
    AppWorkoutSetup _setup;
    AppWorkoutRun _run;

public:

    void initExtend() override ;
    void drawUpdate() override;
    void setButton1() override; // Changed the target parameter select.
    void setButton2() override; // Start the Workout run application
    void setButton3() override{ _canBeClosed = true; }
    void setValue1(int16_t value) override; // Left the application.
    void setValue2(int16_t value) override {}
    void reset() override;
};


#endif //CODEXZIER_VERSATRON_APPWORKOUT_H
