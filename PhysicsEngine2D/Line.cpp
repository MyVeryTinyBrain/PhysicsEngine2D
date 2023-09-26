#define LINE_START	0
#define LINE_END	1

#include "stdafx.h"
#include "Line.h"

Line::Line(const float& x1, const float& y1, const float& x2, const float& y2) : Line({ x1,y1 }, { x2,y2 })
{

}

Line::Line(const Vector2& p1, const Vector2& p2) : Shape(2)
{
	m_vertices[LINE_START] = p1;
	m_vertices[LINE_END] = p2;
	Vector2 relativeVector = p2 - p1;
	m_direction = relativeVector.normalized();
	m_length = relativeVector.magnitude();
	m_position = (p1 + p2) * 0.5f;
}

Line::~Line()
{

}

const Vector2& Line::direction() const
{
	return m_direction;
}

void Line::setDirection(const Vector2& direction)
{
	m_direction = direction;
	m_angle = Vector2::Radian(Vector2::right(), direction);
	UpdateVertices();
}

const float& Line::length() const
{
	return m_length;
}

void Line::setLength(const float& length)
{
	m_length = length;
	UpdateVertices();
}

const Vector2& Line::start() const
{
	return m_vertices[LINE_START];
}

const Vector2& Line::end() const
{
	return m_vertices[LINE_END];
}

const Vector2& Line::position() const
{
	return m_position;
}

void Line::setPosition(const Vector2& position)
{
	m_position = position;
	UpdateVertices();
}

const float& Line::angle() const
{
	return m_angle;
}

void Line::setAngle(const float& radian)
{
	m_angle = radian;
	m_direction = Vector2::Direction(radian);
	UpdateVertices();
}

void Line::UpdateVertices()
{
	m_vertices[LINE_START] = m_position - m_direction * m_length * 0.5f;
	m_vertices[LINE_END] = m_position + m_direction * m_length * 0.5f;
}
