#pragma once
#ifndef __MemoryBrush_h__
#define __MemoryBrush_h__

#include <Windows.h>
#include "RGBColor.h"

class MemoryBrush
{
	HBRUSH m_hBrush;
	RGBColor m_color;
	bool m_nullBrush;
public:
	MemoryBrush();
	MemoryBrush(RGBColor color);
	MemoryBrush(const MemoryBrush& rhs);
	MemoryBrush(MemoryBrush&& rhs) noexcept;
	MemoryBrush& operator = (const MemoryBrush& rhs);
	MemoryBrush& operator = (MemoryBrush&& rhs) noexcept;
	~MemoryBrush();
	operator HBRUSH() const;
	HBRUSH GetHBrush() const;
	RGBColor GetColor() const;
	bool IsNullBrush() const;
	operator bool() const;
	static MemoryBrush MakeNullBrush();
private:
	void Release();
};

#endif
