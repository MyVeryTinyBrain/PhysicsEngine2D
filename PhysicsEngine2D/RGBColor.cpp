#include "stdafx.h"
#include "RGBColor.h"

RGBColor::RGBColor() : RGBColor(0, 0, 0)
{ }

RGBColor::RGBColor(BYTE _red, BYTE _green, BYTE _blue) :
	red(_red), green(_green), blue(_blue), unused(0)
{ }

RGBColor::RGBColor(COLORREF colorReference) :
	red(GetRValue(colorReference)), green(GetGValue(colorReference)), blue(GetBValue(colorReference)), unused(0)
{}

RGBColor::RGBColor(RGBQUAD rgbQuad) :
	red(rgbQuad.rgbRed), green(rgbQuad.rgbGreen), blue(rgbQuad.rgbBlue), unused(rgbQuad.rgbReserved)
{}

RGBColor::operator COLORREF() const
{
	return RGB(red, green, blue);
}

RGBColor::operator RGBQUAD() const
{
	return RGBQUAD{ red,green,blue,unused };
}

RGBColor& RGBColor::operator=(const COLORREF& colorReference)
{
	red = GetRValue(colorReference);
	green = GetGValue(colorReference);
	blue = GetBValue(colorReference);
	return *this;
}

RGBColor& RGBColor::operator=(const RGBQUAD& rgbQuad)
{
	red = rgbQuad.rgbRed;
	green = rgbQuad.rgbGreen;
	blue = rgbQuad.rgbBlue;
	unused = rgbQuad.rgbReserved;
	return *this;
}

RGBColor RGBColor::Red()
{
	return RGBColor(255, 0, 0);
}

RGBColor RGBColor::Green()
{
	return RGBColor(0, 255, 0);
}

RGBColor RGBColor::Blue()
{
	return RGBColor(0, 0, 255);
}

RGBColor RGBColor::Black()
{
	return RGBColor(0, 0, 0);
}

RGBColor RGBColor::White()
{
	return RGBColor(255, 255, 255);
}
