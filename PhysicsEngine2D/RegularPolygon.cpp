#include "stdafx.h"
#include "RegularPolygon.h"
#include "RegularPolygonShape.h"

RegularPolygon::RegularPolygon(float x, float y, float length, float begAngle, size_t n) : Body(1)
{
    m_shapes[0] = new RegularPolygonShape(x, y, length, begAngle, n);
}

RegularPolygon::RegularPolygon(Vector2 position, float length, float begAngle, size_t n) : RegularPolygon(position.x, position.y, length, begAngle, n)
{
}

RegularPolygon::~RegularPolygon()
{
}

const Vector2& RegularPolygon::position() const
{
    return m_shapes[0]->position();
}

void RegularPolygon::setPosition(const Vector2& position)
{
    m_shapes[0]->setPosition(position);
}

const float& RegularPolygon::angle() const
{
    return m_shapes[0]->angle();
}

void RegularPolygon::setAngle(const float& angle)
{
    m_shapes[0]->setAngle(angle);
}

float RegularPolygon::inertia() const
{
    const float& r = m_shapes[0]->radius();
    return (m_mass * r * r) * 0.5f;
}

void RegularPolygon::Draw(MemoryDC& memDC) const
{
    memDC.SetBrush(MemoryBrush::MakeNullBrush());
    memDC.SetPen(0, 255, 0, 1);
    for (size_t i = 0; i < m_shapes[0]->vertexCount(); ++i)
    {
        size_t next = i + 1;
        if (next == m_shapes[0]->vertexCount()) next = 0;
        const Vector2& p1 = m_shapes[0]->vertex(i);
        const Vector2& p2 = m_shapes[0]->vertex(next);
        memDC.DrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}

const float& RegularPolygon::length() const
{
    RegularPolygonShape* regularPolygon = static_cast<RegularPolygonShape*>(m_shapes[0]);
    return regularPolygon->length();
}

const float& RegularPolygon::radius() const
{
    return m_shapes[0]->radius();
}
