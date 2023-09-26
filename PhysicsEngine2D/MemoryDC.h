#pragma once
#ifndef __MemoryDC_h__
#define __MemoryDC_h__

#include <Windows.h>
#include "MemoryPen.h"
#include "MemoryBrush.h"

class MemoryDC
{
	HDC m_hDC;
	HBITMAP m_hBitmap;
	MemoryPen m_pen;
	MemoryBrush m_brush;
	int m_width;
	int m_height;
public:
	MemoryDC(HDC hDC, int width, int height);
	~MemoryDC();
	operator HDC () const;
	HDC GetHDC() const;
	operator HBITMAP() const;
	HBITMAP GetHBitmap() const;
	int width() const;
	int height() const;
	void SetDefaultCoordinate();
	void SetYInversedCoordinate();
	void SetPen(const MemoryPen& pen);
	void SetPen(BYTE r, BYTE g, BYTE b, int width);
	void SetBrush(const MemoryBrush& brush);
	void SetBrush(BYTE r, BYTE g, BYTE b);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawCircle(float x, float y, float r);
	void DrawRect(float x, float y, float width, float height);
	void WriteText(float x, float y, LPCTSTR text);
};

#endif
