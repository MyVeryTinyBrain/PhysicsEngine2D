#include "stdafx.h"
#include "MemoryDC.h"

MemoryDC::MemoryDC(HDC hDC, int width, int height)
{
	m_hDC = CreateCompatibleDC(hDC);
	m_hBitmap = CreateCompatibleBitmap(hDC, width, height);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
	DeleteObject(oldBitmap);
	m_width = width;
	m_height = height;
}

MemoryDC::~MemoryDC()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBitmap);
}

MemoryDC::operator HDC() const
{
	return m_hDC;
}

HDC MemoryDC::GetHDC() const
{
	return m_hDC;
}

MemoryDC::operator HBITMAP() const
{
	return m_hBitmap;
}

HBITMAP MemoryDC::GetHBitmap() const
{
	return m_hBitmap;
}

int MemoryDC::width() const
{
	return m_width;
}

int MemoryDC::height() const
{
	return m_height;
}

void MemoryDC::SetDefaultCoordinate()
{
	SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM m2;
	m2.eM11 = 1;
	m2.eM12 = 0;
	m2.eM21 = 0;
	m2.eM22 = 1;
	m2.eDx = 0;
	m2.eDy = 0;
	SetWorldTransform(m_hDC, &m2);
	SetGraphicsMode(m_hDC, GM_COMPATIBLE);
}

void MemoryDC::SetYInversedCoordinate()
{
	SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM m1;
	m1.eM11 = 1;
	m1.eM12 = 0;
	m1.eM21 = 0;
	m1.eM22 = -1;
	m1.eDx = 0;
	m1.eDy = m_height;
	SetWorldTransform(m_hDC, &m1);
}

void MemoryDC::SetPen(const MemoryPen& pen)
{
	m_pen = pen;
	HPEN oldPen = (HPEN)SelectObject(m_hDC, m_pen);
	DeleteObject(oldPen);
}

void MemoryDC::SetPen(BYTE r, BYTE g, BYTE b, int width)
{
	m_pen = MemoryPen(RGBColor(r, g, b), width);
	HPEN oldPen = (HPEN)SelectObject(m_hDC, m_pen);
	DeleteObject(oldPen);
}

void MemoryDC::SetBrush(const MemoryBrush& brush)
{
	m_brush = brush;
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, m_brush);
	DeleteObject(oldBrush);
}

void MemoryDC::SetBrush(BYTE r, BYTE g, BYTE b)
{
	m_brush = MemoryBrush(RGBColor(r, g, b));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, m_brush);
	DeleteObject(oldBrush);
}

void MemoryDC::DrawLine(float x1, float y1, float x2, float y2)
{
	MoveToEx(m_hDC, x1, y1, NULL);
	LineTo(m_hDC, x2, y2);
}

void MemoryDC::DrawCircle(float x, float y, float r)
{
	Ellipse(m_hDC, x - r, y - r, x + r, y + r);
}

void MemoryDC::DrawRect(float x, float y, float width, float height)
{
	width /= 2;
	height /= 2;
	Rectangle(m_hDC, x - width, y - height, x + width, y + height);
}

void MemoryDC::WriteText(float x, float y, LPCTSTR text)
{
	size_t len = _tcslen(text);
	SetBkMode(m_hDC, TRANSPARENT);
	TextOut(m_hDC, x, y, text, len);
	SetBkMode(m_hDC, OPAQUE);
}
