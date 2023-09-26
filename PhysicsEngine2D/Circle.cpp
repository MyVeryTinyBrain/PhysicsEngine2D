#include "stdafx.h"
#include "Circle.h"

Circle::Circle(const float& x, const float& y, const float& radius) : Shape(0)
{
	m_position.x = x;
	m_position.y = y;
	m_radius = radius;
}

Circle::Circle(const Vector2& position, const float& radius) : Shape(0)
{
	m_position = position;
	m_radius = radius;
}

Circle::~Circle()
{
}

const Vector2& Circle::position() const
{
	return m_position;
}

void Circle::setPosition(const Vector2& position)
{
	m_position = position;
}

const float& Circle::angle() const
{
	return m_angle;
}

void Circle::setAngle(const float& radian)
{
	m_angle = radian;
}
