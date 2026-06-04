//
// Created by codexzier on 04.06.26.
//

#pragma once
#include <stdint.h>
#include "GC9A01_LTSM.hpp"

#ifndef CODEXZIER_VERSATRON_IDRAWABLE_H
#define CODEXZIER_VERSATRON_IDRAWABLE_H

class IDrawable {
public:
    /*
     * Virtueller Destruktor für korrekte Polymorphie
     */
    virtual ~IDrawable() = default;

    /**
     * Initialize the ring segment display with the given TFT display and colors.
     * @param tft The GC9A01_LTSM TFT display object.
     * @param colorOn The color to use for segments that are on.
     * @param colorOff The color to use for segments that are off.
     * @param colorText The color to use for text.
     */
    virtual void init(GC9A01_LTSM &tft, uint16_t colorOn, uint16_t colorOff, uint16_t colorText) = 0;
    virtual void initExtend() = 0;
    /**
     * Draw content.
     */
    virtual void drawUpdate() = 0;

    /**
     * Button execution 1.
     */
    virtual void setButton1() = 0;
    /**
     * Button execution 2.
     */
    virtual void setButton2() = 0;

protected:
    GC9A01_LTSM *_tft = nullptr;
    uint16_t _colorOn = 0;
    uint16_t _colorOff = 0;
    uint16_t _colorText = 0;
    bool _hasDraw = false;
};

#endif //CODEXZIER_VERSATRON_IDRAWABLE_H
