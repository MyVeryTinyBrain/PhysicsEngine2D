#include "stdafx.h"
#include "Ball.h"
#include "Circle.h"
#include <cassert>

Ball::Ball(float x, float y, float r) : Body(1)
{
	m_shapes[0] = new Circle(x, y, r);
}

Ball::~Ball()
{
}

const Vector2& Ball::position() const
{
	return m_shapes[0]->position();
}

void Ball::setPosition(const Vector2& position)
{
	m_shapes[0]->setPosition(position);
}

const float& Ball::angle() const
{
	return m_shapes[0]->angle();
}

void Ball::setAngle(const float& angle)
{
	m_shapes[0]->setAngle(angle);
}

float Ball::inertia() const
{
	Circle* circle = static_cast<Circle*>(m_shapes[0]);
	const float& r = circle->radius();
	return (m_mass * r * r) * 0.5f;
}

void Ball::Draw(MemoryDC & memDC) const
{
	Circle* circle = static_cast<Circle*>(m_shapes[0]);
	const Vector2& position = circle->position();
	const float& angle = circle->angle();
	const float& radius = circle->radius();
	memDC.SetBrush(MemoryBrush::MakeNullBrush());
	memDC.SetPen(0, 255, 0, 1);
	memDC.DrawCircle(position.x, position.y, radius);
	memDC.DrawLine(position.x, position.y, position.x + cosf(angle) * radius, position.y + sinf(angle) * radius);
}

const float& Ball::radius() const
{
	return m_shapes[0]->radius();
}
