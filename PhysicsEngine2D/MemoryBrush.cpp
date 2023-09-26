#include "stdafx.h"
#include "MemoryBrush.h"
#include <utility>

MemoryBrush::MemoryBrush()
{
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	m_color = RGBColor(0, 255, 0);
	m_nullBrush = true;
}

MemoryBrush::MemoryBrush(RGBColor color)
{
	m_hBrush = CreateSolidBrush(color);
	m_color = color;
	m_nullBrush = false;
}

MemoryBrush::MemoryBrush(const MemoryBrush& rhs)
{
	*this = rhs;
}

MemoryBrush::MemoryBrush(MemoryBrush&& rhs) noexcept
{
	*this = std::move(rhs);
}

MemoryBrush& MemoryBrush::operator=(const MemoryBrush& rhs)
{
	if (rhs.m_nullBrush) m_hBrush = rhs.m_hBrush;
	else if (rhs) m_hBrush = CreateSolidBrush(rhs.m_color);
	else m_hBrush = 0;
	m_color = rhs.m_color;
	m_nullBrush = rhs.m_nullBrush;
	return *this;
}

MemoryBrush& MemoryBrush::operator=(MemoryBrush&& rhs) noexcept
{
	m_hBrush = rhs.m_hBrush;
	m_color = rhs.m_color;
	m_nullBrush = rhs.m_nullBrush;
	rhs.m_hBrush = 0;
	return *this;
}

MemoryBrush::~MemoryBrush()
{
	Release();
}

MemoryBrush::operator HBRUSH() const
{
	return m_hBrush;
}

HBRUSH MemoryBrush::GetHBrush() const
{
	return m_hBrush;
}

RGBColor MemoryBrush::GetColor() const
{
	return m_color;
}

bool MemoryBrush::IsNullBrush() const
{
	return m_nullBrush;
}

MemoryBrush::operator bool() const
{
	return m_hBrush != 0;
}

MemoryBrush MemoryBrush::MakeNullBrush()
{
	return MemoryBrush();
}

void MemoryBrush::Release()
{
	if (!m_nullBrush && m_hBrush)
		DeleteObject(m_hBrush);
	m_hBrush = 0;
}
