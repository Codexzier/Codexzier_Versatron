//
// Created by codexzier on 29.04.26.
//

#include "ControlRingSegmentDisplay.h"

#include <algorithm>
#include <math.h>
#include "fonts_LTSM/FontArialBold_LTSM.hpp"    // 16x16 pixels


void ControlRingSegmentDisplay::drawInitGaugeSetup(int countSegments) {
    _segmentsCount = countSegments;
    float segmentWidth = 3.0; // Breite des Segments in Grad für die Optik
    float angle = 0;
    _segmentMultiplicator = 360.0 / _segmentsCount;
    segmentWidth = _segmentMultiplicator / 2.0;
    for (int index = 0; index < _segmentsCount; index++) {
        _segmentsOnRing[index] = false;

        angle = _startAngle + (index * _segmentMultiplicator);
        drawGaugeSegment(angle, _colorOff, segmentWidth);
    }
}

void ControlRingSegmentDisplay::setValue(int value)
{
    if (value < 0 || value > _segmentsCount) {
        return;
    }
    _segmentValueOn = value / _angleStep;
}

void ControlRingSegmentDisplay::setColor(uint16_t color) {
    _colorOn = color;
}

int ControlRingSegmentDisplay::GetValue() {
    return static_cast<int>(_segmentValueOn * _angleStep);
}

void ControlRingSegmentDisplay::drawGaugeUpdate() {

    if (_segmentIndex >= _segmentsCount) {
        _segmentIndex = 0;
    }

    float angle = _startAngle + (_segmentIndex * _segmentMultiplicator);

    uint16_t color1 = _colorOn;
    bool segmentOn = true;
    if(_segmentValueOn <= _segmentIndex) {
        color1 = _colorOff;
        segmentOn = false;
    }

    if (_segmentsOnRing[_segmentIndex] == segmentOn) {
        _segmentIndex++;
        return;
    }
    _segmentsOnRing[_segmentIndex] = segmentOn;

    drawGaugeSegment(angle, color1, _segmentMultiplicator / 2.0);

    _segmentIndex++;
}

// ========================================================================================
// Zeichnet ein einzelnes Segment für die Anzeige (Licht oder Lautstärke)
// @param angleDeg Der Winkel in Grad (0° ist rechts/3 Uhr, 270° ist oben/12 Uhr)
// @param color Die Farbe des Segments (RGB565)
// @param Äußerer Rand des Balkens (fast am Glas)
// @param Innerer Rand (Dicke des Balkens = 15px)
void ControlRingSegmentDisplay::drawGaugeSegment(
        const float angleDeg,
        const uint16_t color,
        const float segmentWidth) {

    // Feste Werte für das Design der Camping-Lampe
    constexpr int centerX = 120;    // Mitte des 240x240 Displays
    constexpr int centerY = 120;

    // Umrechnung von Winkeln zwischen Grad und Radiant.
    float shiftAngle = angleDeg - 90.0;
    const float rad = M_PI * shiftAngle / 180.0;
    const float radOffset = (segmentWidth / 2.0) * M_PI / 180.0;

    // Berechnung der 4 Eckpunkte des Segments für ein sauberes Rechteck
    // Punkt A & B (Innen), Punkt C & D (Außen)
    const int xA = centerX + cos(rad - radOffset) * _radiusInner;
    const int yA = centerY + sin(rad - radOffset) * _radiusInner;

    const int xB = centerX + cos(rad + radOffset) * _radiusInner;
    const int yB = centerY + sin(rad + radOffset) * _radiusInner;

    const int xC = centerX + cos(rad - radOffset) * _radiusOuter;
    const int yC = centerY + sin(rad - radOffset) * _radiusOuter;

    const int xD = centerX + cos(rad + radOffset) * _radiusOuter;
    const int yD = centerY + sin(rad + radOffset) * _radiusOuter;

    // Zeichnen des Segments.
    // Wir füllen das Segment, indem wir zwei Dreiecke zeichnen (Standard-Verfahren für Polygone)
    _tft->fillTriangle(xA, yA, xB, yB, xC, yC, color);
    _tft->fillTriangle(xB, yB, xC, yC, xD, yD, color);
}

