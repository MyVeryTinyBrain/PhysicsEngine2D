#include "stdafx.h"
#include "Wall.h"
#include "Line.h"

Wall::Wall(float x1, float y1, float x2, float y2) : Wall({ x1,y1 }, { x2,y2 })
{
}

Wall::Wall(Vector2 start, Vector2 end) : Body(1)
{
	m_shapes[0] = new Line(start, end);
}

Wall::~Wall()
{
}

const Vector2& Wall::position() const
{
	return m_shapes[0]->position();
}

void Wall::setPosition(const Vector2& position)
{
	m_shapes[0]->setPosition(position);
}

const float& Wall::angle() const
{
	return m_shapes[0]->angle();
}

void Wall::setAngle(const float& angle)
{
	m_shapes[0]->setAngle(angle);
}

float Wall::inertia() const
{
	Line* line = static_cast<Line*>(m_shapes[0]);
	float length = line->length();
	return (m_mass * length * length) / 12.0f;
}

void Wall::Draw(MemoryDC& memDC) const
{
	Line* line = static_cast<Line*>(m_shapes[0]);
	const Vector2& beg = line->start();
	const Vector2& end = line->end();
	memDC.SetBrush(MemoryBrush::MakeNullBrush());
	memDC.SetPen(0, 255, 0, 1);
	memDC.DrawLine(beg.x, beg.y, end.x, end.y);
}
