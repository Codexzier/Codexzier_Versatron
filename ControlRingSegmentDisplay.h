//
// Created by codexzier on 29.04.26.
//

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"

#ifndef CODEXZIER_VERSATRON_RINGSEGMENTDISPLAY_H
#define CODEXZIER_VERSATRON_RINGSEGMENTDISPLAY_H


class ControlRingSegmentDisplay {

private:
    GC9A01_LTSM *_tft;
    uint16_t _colorOn;
    uint16_t _colorOff;

    const int _segmentsCount = 60;
    const float _startAngle = 0.0f;
    const float _angleStep = 1.0f;
    int _segmentIndex = 0;
    int _segmentValueOn = 0.0f;

    bool _segmentsOnRing[60];
    int _radiusOuter = 118;
    int _radiusInner = 112;

    void drawGaugeSegment(
        float angleDeg,
        uint16_t color,
        float segmentWidth);

public:
    explicit ControlRingSegmentDisplay(int radiusOuter, int radiusInner)
        : _tft(nullptr), _colorOn(0), _colorOff(0),
            _radiusOuter(radiusOuter), _radiusInner(radiusInner) { }

    /**
     * Initialize the ring segment display with the given TFT display and colors.
     * @param tft The GC9A01_LTSM TFT display object.
     * @param colorOn The color to use for segments that are on.
     * @param colorOff The color to use for segments that are off.
     */
    void init(GC9A01_LTSM &tft,
        const uint16_t colorOn,
        const uint16_t colorOff) {
        _tft = &tft;
        _colorOn = colorOn;
        _colorOff = colorOff;
    }
    void drawInitGauge();
    void drawInitGaugeSetup(int countSegments);

    /**
     * Set the value of the ring segment display.
     * @param value The value to set, between 0 and 100.
     */
    void setValue(int value);

    void setColor(uint16_t color);

    /**
     * Get the current value of the ring segment display.
     * @return The current value, between 0 and 100.
     */
    int GetValue();

    /**
     * Update the display with the current value.
     */
    void drawGaugeUpdate();
};


#endif //CODEXZIER_VERSATRON_RINGSEGMENTDISPLAY_H
