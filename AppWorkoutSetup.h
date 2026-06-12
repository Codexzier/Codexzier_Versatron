//
// Created by codexzier on 10.05.26.
//

#ifndef CODEXZIER_VERSATRON_APPWORKOUTSETUP_H
#define CODEXZIER_VERSATRON_APPWORKOUTSETUP_H

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"

enum SelectSetup {
    TimeExecution,
    TimeBreak,
    CountRound
};

class AppWorkoutSetup {

    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;
    uint16_t _colorText;

    const int16_t _startX = 50;
    const int16_t _startY = 70;

    void drawTextAndTime(int x, int y, const char* text, int value);
    bool _option1SetupHasDraw = false;

    SelectSetup _selectSetup = TimeExecution;
    int16_t _lastSelectSetupPointerPositionY = 0;
    uint16_t _secondsExecutionMax = 30;
    uint16_t _secondsBreakMax = 30;
    uint16_t _roundMax = 5;

    void drawSetupValues();
    void drawSelectPointer();

public:
    AppWorkoutSetup()
    : _tft(nullptr), _colorOn(0), _colorOff(0), _colorText(0) {}

    /**
     * Initialize the ring segment display with the given TFT display and colors.
     * @param tft The GC9A01_LTSM TFT display object.
     * @param colorOn The color to use for segments that are on.
     * @param colorOff The color to use for segments that are off.
     * @param colorText
     */
    void init(GC9A01_LTSM &tft,
              const uint16_t colorOn,
              const uint16_t colorOff,
              const uint16_t colorText) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
        _colorText = colorText;
    }

    /**
     * draw content
     */
    void drawUpdate();

    /**
     * reset all set to start parameter.
     */
    void reset();

    /**
     * Set the value to setup parameter for execution, break and rounds.
     * @param value
     */
    void setValue1(int16_t value);

    /**
     * Push the button to change the target parameter.
     */
    void setButton1();

    /**
     * Get the max second execution.
     * @return max second for execution.
     */
    uint16_t getExecutionMax() const;

    /**
     * Get the max second break.
     * @return max second for break.
     */
    uint16_t getBreakMax() const;

    /**
     * Get the max round of workout.
     * @return max round of workout.
     */
    uint16_t getRoundMax() const;
};


#endif //CODEXZIER_VERSATRON_APPWORKOUTSETUP_H
