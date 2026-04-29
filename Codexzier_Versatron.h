//
// Created by codexzier on 26.04.26.
//
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "GC9A01_LTSM.hpp"


#ifndef CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
#define CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H

class Codexzier_Versatron {

    bool _segmentsOnRing1[60];
    bool _segmentsOnRing2[60];
    bool _segmentsOnRing3[60];
    uint16_t _colorOn;
    uint16_t _colorOff;

    int _radiusOuter1 = 118;
    int _radiusInner1 = 112;
    int _radiusOuter2 = 108;
    int _radiusInner2 = 100;
    int _radiusOuter3 = 96;
    int _radiusInner3 = 88;

    int _segmentIndexReset = 0;
    bool _segmentIndexResetFlag = false;
    int _segmentIndex = 0;
    int _segmentIndexMax = 60;

    int _segmentValue1 = 0;
    int _segmentValue2 = 0;
    int _segmentValue3 = 0;

    void drawGaugeSegmentsByParameter(
        GC9A01_LTSM &tft,
        int8_t ring,
        bool segmentOn,
        bool bySegmentOn,
        int index,
        float angle,
        uint16_t color);

public:
    Codexzier_Versatron();

    void updateSegmentIndex(GC9A01_LTSM &tft);

    void drawInitGaugeSegments(
        GC9A01_LTSM &tft,
        uint16_t gaugeColor,
        uint16_t colorOff);
    void drawGaugeSegmentReset(
        GC9A01_LTSM &tft,
        int8_t ring);
    void drawGaugeSegments(
        GC9A01_LTSM &tft,
        int16_t value,
        float startAngle,
        int8_t ring);
    void drawSetValueForGaugeSegments(
        int16_t value,
        int8_t ring);

    static void drawGaugeSegment(
        GC9A01_LTSM &tft,
        float angleDeg,
        uint16_t color,
        int radiusOuter,
        int radiusInner);

};

#endif //CODEXZIER_VERSATRON_CODEXZIER_VERSATRON_H
