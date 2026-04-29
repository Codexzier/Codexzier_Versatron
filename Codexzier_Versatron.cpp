//
// Created by codexzier on 26.04.26.
//

#include "Codexzier_Versatron.h"
#include <math.h>
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels
#include "fonts_LTSM/FontPico_LTSM.hpp"         // 8x12 pixels
#include "fonts_LTSM/FontSinclairS_LTSM.hpp"    // 8x8 pixels

Codexzier_Versatron::Codexzier_Versatron() {
}

void Codexzier_Versatron::updateSegmentIndex(GC9A01_LTSM &tft) {
    if (_segmentIndex >= _segmentIndexMax) {
        _segmentIndex = 0;
    } else {
        _segmentIndex++;
    }

    if (_segmentIndexResetFlag) {

        if (_segmentIndexReset >= _segmentIndexMax) {
            _segmentIndexReset = 0;
            _segmentIndexResetFlag = false;
        } else {
            _segmentIndexReset++;
        }
    }

    drawGaugeSegments(tft, _segmentValue1, 0, 0);
    drawGaugeSegments(tft, _segmentValue2, 0, 1);
    drawGaugeSegments(tft, _segmentValue3, 0, 2);
}

void Codexzier_Versatron::drawInitGaugeSegments(
    GC9A01_LTSM &tft,
    uint16_t colorOn,
    const uint16_t colorOff) {

    _colorOn = colorOn;
    _colorOff = colorOff;

    float angle = 0;
    for (int index = 0; index < 60; index++) {
        _segmentsOnRing1[index] = false;
        _segmentsOnRing2[index] = false;
        _segmentsOnRing3[index] = false;

        angle = 45 + ((7 - index) * 6);
        drawGaugeSegment(tft, angle, _colorOff, _radiusOuter1, _radiusInner1);
        drawGaugeSegment(tft, angle, _colorOff, _radiusOuter2, _radiusInner2);
        drawGaugeSegment(tft, angle, _colorOff, _radiusOuter3, _radiusInner3);
    }
}

void Codexzier_Versatron::drawGaugeSegmentReset(
    GC9A01_LTSM &tft,
    const int8_t ring) {

    _segmentIndexResetFlag = true;

    const uint16_t color1 = _colorOff;
    float angle = 0;
    //for (int index = 0; index < 60; index++) {

    int index = _segmentIndexReset;
    angle = 45 + ((7 - index) * 6);
    drawGaugeSegmentsByParameter(tft, ring, false, false, index, angle, color1);
    //}
}

void Codexzier_Versatron::drawGaugeSegments(
    GC9A01_LTSM &tft,
    const int16_t value,
    const float startAngle,
    const int8_t ring) {

    if (_segmentIndexResetFlag) return;

    constexpr float step = 1.0;
    const float segmentValueOn = value / step;

    float angle = 0;

    //for(int index = 0; index < 60; index++) {
    const int index = _segmentIndex;

    angle = 45 + startAngle + ((7 - index) * 6);

    uint16_t color1 = _colorOn;
    bool segmentOn = true;
    if(segmentValueOn <= index) {
        color1 = _colorOff;
        segmentOn = false;
    }

    drawGaugeSegmentsByParameter(tft, ring, segmentOn, true, index, angle, color1);
    //}
}

void Codexzier_Versatron::drawSetValueForGaugeSegments(
    int16_t value,
    int8_t ring) {

    switch (ring) {
        case 0: _segmentValue1 = value; break;
        case 1: _segmentValue2 = value; break;
        case 2: _segmentValue3 = value; break;
        default: break;
    }
}

void Codexzier_Versatron::drawGaugeSegmentsByParameter(
    GC9A01_LTSM &tft,
    const int8_t ring,
    const bool segmentOn,
    const bool bySegmentOn,
    const int index,
    const float angle,
    const uint16_t color){

    switch (ring) {
        case(0): {
            if (_segmentsOnRing1[index] == segmentOn && bySegmentOn) return;
            _segmentsOnRing1[index] = segmentOn;
            drawGaugeSegment(tft, angle, color, _radiusOuter1, _radiusInner1);
            break;
        }
        case(1): {
            if (_segmentsOnRing2[index] == segmentOn) return;
            _segmentsOnRing2[index] = segmentOn;
            drawGaugeSegment(tft, angle, color, _radiusOuter2, _radiusInner2);
            break;
        }
        case(2): {
            if (_segmentsOnRing3[index] == segmentOn) return;
            _segmentsOnRing3[index] = segmentOn;
            drawGaugeSegment(tft, angle, color, _radiusOuter3, _radiusInner3);
            break;
        }
        default: {
            break;
        }
    }
}

// ========================================================================================
// Zeichnet ein einzelnes Segment für die Anzeige (Licht oder Lautstärke)
// @param angleDeg Der Winkel in Grad (0° ist rechts/3 Uhr, 270° ist oben/12 Uhr)
// @param color Die Farbe des Segments (RGB565)
// @param Äußerer Rand des Balkens (fast am Glas)
// @param Innerer Rand (Dicke des Balkens = 15px)
void Codexzier_Versatron::drawGaugeSegment(
    GC9A01_LTSM &tft,
    const float angleDeg,
    const uint16_t color,
    const int radiusOuter,
    const int radiusInner) {

    // Feste Werte für das Design der Camping-Lampe
    constexpr int centerX = 120;    // Mitte des 240x240 Displays
    constexpr int centerY = 120;
    constexpr float segmentWidth = 3.0; // Breite des Segments in Grad für die Optik

    // Umrechnung von Winkeln zwischen Grad und Radiant.
    const float rad = M_PI * angleDeg / 180.0;
    constexpr float radOffset = (segmentWidth / 2.0) * M_PI / 180.0;

    // Berechnung der 4 Eckpunkte des Segments für ein sauberes Rechteck
    // Punkt A & B (Innen), Punkt C & D (Außen)
    const int xA = centerX + cos(rad - radOffset) * radiusInner;
    const int yA = centerY + sin(rad - radOffset) * radiusInner;

    const int xB = centerX + cos(rad + radOffset) * radiusInner;
    const int yB = centerY + sin(rad + radOffset) * radiusInner;

    const int xC = centerX + cos(rad - radOffset) * radiusOuter;
    const int yC = centerY + sin(rad - radOffset) * radiusOuter;

    const int xD = centerX + cos(rad + radOffset) * radiusOuter;
    const int yD = centerY + sin(rad + radOffset) * radiusOuter;

    // Zeichnen des Segments.
    // Wir füllen das Segment, indem wir zwei Dreiecke zeichnen (Standard-Verfahren für Polygone)
    tft.fillTriangle(xA, yA, xB, yB, xC, yC, color);
    tft.fillTriangle(xB, yB, xC, yC, xD, yD, color);
}