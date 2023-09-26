#include "stdafx.h"
#include "Box.h"
#include "Rect.h"

Box::Box(Vector2 leftTop, Vector2 rightBottom) : Body(1)
{
	m_shapes[0] = new Rect(leftTop, rightBottom);
}

Box::Box(float left, float top, float right, float bottom) : Box({ left,top }, { right,bottom })
{
}

Box::Box(Vector2 leftTop, Vector2 rightTop, float height) : Body(1)
{
	m_shapes[0] = new Rect(leftTop, rightTop, height);
}

Box::Box(float width, Vector2 leftTop, Vector2 leftBottom) : Body(1)
{
	m_shapes[0] = new Rect(width, leftTop, leftBottom);
}

Box::~Box()
{
}

const Vector2& Box::position() const
{
	return m_shapes[0]->position();
}

void Box::setPosition(const Vector2& position)
{
	m_shapes[0]->setPosition(position);
}

const float& Box::angle() const
{
	return m_shapes[0]->angle();
}

void Box::setAngle(const float& angle)
{
	return m_shapes[0]->setAngle(angle);
}

float Box::inertia() const
{
	Rect* rect = static_cast<Rect*>(m_shapes[0]);
	float width = rect->width();
	float height = rect->height();
	float length = width > height ? width : height;
	length *= 2;
	return (m_mass * length * length) / 12.0f;
}

void Box::Draw(MemoryDC& memDC) const
{
	Rect* rect = static_cast<Rect*>(m_shapes[0]);
	const Vector2& p1 = rect->vertex(0);
	const Vector2& p2 = rect->vertex(1);
	const Vector2& p3 = rect->vertex(2);
	const Vector2& p4 = rect->vertex(3);
	memDC.SetBrush(MemoryBrush::MakeNullBrush());
	memDC.SetPen(0, 255, 0, 1);
	memDC.DrawLine(p1.x, p1.y, p2.x, p2.y);
	memDC.DrawLine(p2.x, p2.y, p3.x, p3.y);
	memDC.DrawLine(p3.x, p3.y, p4.x, p4.y);
	memDC.DrawLine(p4.x, p4.y, p1.x, p1.y);
}
