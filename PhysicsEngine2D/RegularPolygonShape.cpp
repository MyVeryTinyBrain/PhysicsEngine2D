#include "stdafx.h"
#include "RegularPolygonShape.h"

RegularPolygonShape::RegularPolygonShape(float x, float y, float length, float begAngle, size_t n) : Shape(n)
{
    m_position = { x,y };
    m_radius = length;
    m_begAngle = begAngle;
    UpdateVertices();
}

RegularPolygonShape::RegularPolygonShape(Vector2 position, float length, float begAngle, size_t n) : RegularPolygonShape(position.x, position.y, length, begAngle, n)
{
}

RegularPolygonShape::~RegularPolygonShape()
{
}

const Vector2& RegularPolygonShape::position() const
{
    return m_position;
}

void RegularPolygonShape::setPosition(const Vector2& position)
{
    m_position = position;
    UpdateVertices();
}

const float& RegularPolygonShape::angle() const
{
    return m_angle;
}

void RegularPolygonShape::setAngle(const float& radian)
{
    m_angle = radian;
    UpdateVertices();
}

const float& RegularPolygonShape::length() const
{
    return m_radius;
}

void RegularPolygonShape::UpdateVertices()
{
    for (size_t i = 0; i < m_vertexCount; ++i)
    {
        float percent = (-1) * (float)i / (float)m_vertexCount;
        float angle = percent * TAU + m_angle + m_begAngle;
        Vector2 direction = Vector2::Direction(angle);
        m_vertices[i] = direction * m_radius + m_position;
    }
}
