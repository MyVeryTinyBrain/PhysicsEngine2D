#pragma once
#ifndef __MemoryPen_h__
#define __MemoryPen_h__

#include <Windows.h>
#include "RGBColor.h"

class MemoryPen
{
	HPEN m_hPen;
	RGBColor m_color;
	int m_width;
	bool m_nullPen;
public:
	MemoryPen();
	MemoryPen(RGBColor color, int width);
	MemoryPen& operator = (const MemoryPen& rhs);
	MemoryPen& operator = (MemoryPen&& rhs) noexcept;
	MemoryPen(const MemoryPen& rhs);
	MemoryPen(MemoryPen&& rhs) noexcept;
	~MemoryPen();
	operator HPEN() const;
	HPEN GetHPen() const;
	RGBColor GetColor() const;
	bool IsNullPen() const;
	operator bool() const;
	static MemoryPen MakeNullPen();
private:
	void Release();
};

#endif
