#pragma once
#ifndef __RGBColor_h__
#define __RGBColor_h__

#include <Windows.h>

struct RGBColor
{
    BYTE red;
    BYTE green;
    BYTE blue;
    BYTE unused;
    RGBColor();
    RGBColor(BYTE _red, BYTE _green, BYTE _blue);
    RGBColor(COLORREF colorReference);
    RGBColor(RGBQUAD rgbQuad);
    operator COLORREF() const;
    operator RGBQUAD() const;
    RGBColor& operator = (const COLORREF& colorReference);
    RGBColor& operator = (const RGBQUAD& rgbQuad);
    static RGBColor Red();
    static RGBColor Green();
    static RGBColor Blue();
    static RGBColor Black();
    static RGBColor White();
};

#endif 
