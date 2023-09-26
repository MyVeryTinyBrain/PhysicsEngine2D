#include "stdafx.h"
#include "MemoryPen.h"
#include <utility>

MemoryPen::MemoryPen()
{
	m_hPen = (HPEN)GetStockObject(NULL_PEN);
	m_color = 0;
	m_width = 0;
	m_nullPen = true;
}

MemoryPen::MemoryPen(RGBColor color, int width)
{
	m_hPen = CreatePen(PS_SOLID, width, RGB(color.red, color.green, color.blue));
	m_color = color;
	m_width = width;
	m_nullPen = false;
}

MemoryPen& MemoryPen::operator=(const MemoryPen& rhs)
{
	if (rhs.m_nullPen) m_hPen = rhs.m_hPen;
	else if (rhs) m_hPen = CreatePen(PS_SOLID, rhs.m_width, rhs.m_color);
	else m_hPen = 0;
	m_color = rhs.m_color;
	m_width = rhs.m_width;
	m_nullPen = rhs.m_nullPen;
	return *this;
}

MemoryPen& MemoryPen::operator=(MemoryPen&& rhs) noexcept
{
	m_hPen = rhs.m_hPen;
	m_color = rhs.m_color;
	m_width = rhs.m_width;
	m_nullPen = rhs.m_nullPen;
	rhs.m_hPen = 0;
	return *this;
}

MemoryPen::MemoryPen(const MemoryPen& rhs)
{
	*this = rhs;
}

MemoryPen::MemoryPen(MemoryPen&& rhs) noexcept
{
	*this = std::move(rhs);
}

MemoryPen::~MemoryPen()
{
	Release();
}

MemoryPen::operator HPEN() const
{
	return m_hPen;
}

HPEN MemoryPen::GetHPen() const
{
	return m_hPen;
}

RGBColor MemoryPen::GetColor() const
{
	return m_color;
}

bool MemoryPen::IsNullPen() const
{
	return m_nullPen;
}

MemoryPen::operator bool() const
{
	return m_hPen != 0;
}

MemoryPen MemoryPen::MakeNullPen()
{
	return MemoryPen();
}

void MemoryPen::Release()
{
	if (!m_nullPen && m_hPen)
		DeleteObject(m_hPen);
	m_hPen = 0;
}
