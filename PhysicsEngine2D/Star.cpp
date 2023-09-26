#include "stdafx.h"
#include "Star.h"
#include "RegularPolygonShape.h"

#define TRI1    0
#define TRI2    1

Star::Star(float x, float y, float radius) : Body(2)
{
    m_shapes[TRI1] = new RegularPolygonShape(x, y, radius, 90 * DEG2RAD, 3);
    m_shapes[TRI2] = new RegularPolygonShape(x, y, radius, 150 * DEG2RAD, 3);
}

Star::Star(Vector2 position, float radius) : Star(position.x, position.y, radius)
{
}

Star::~Star()
{
}

const Vector2& Star::position() const
{
    return m_shapes[TRI1]->position();
}

void Star::setPosition(const Vector2& position)
{
    m_shapes[TRI1]->setPosition(position);
    m_shapes[TRI2]->setPosition(position);
}

const float& Star::angle() const
{
    return m_shapes[TRI1]->angle();
}

void Star::setAngle(const float& angle)
{
    m_shapes[TRI1]->setAngle(angle);
    m_shapes[TRI2]->setAngle(angle);
}

float Star::inertia() const
{
    float length = 2 * m_shapes[TRI1]->radius();
    return (m_mass * length * length) * 0.5f;
}

void Star::Draw(MemoryDC& memDC) const
{
    memDC.SetBrush(MemoryBrush::MakeNullBrush());
    memDC.SetPen(0, 255, 0, 1);
    memDC.DrawLine(m_shapes[TRI1]->vertex(0).x, m_shapes[TRI1]->vertex(0).y, m_shapes[TRI1]->vertex(1).x, m_shapes[TRI1]->vertex(1).y);
    memDC.DrawLine(m_shapes[TRI1]->vertex(1).x, m_shapes[TRI1]->vertex(1).y, m_shapes[TRI1]->vertex(2).x, m_shapes[TRI1]->vertex(2).y);
    memDC.DrawLine(m_shapes[TRI1]->vertex(2).x, m_shapes[TRI1]->vertex(2).y, m_shapes[TRI1]->vertex(0).x, m_shapes[TRI1]->vertex(0).y);
    memDC.DrawLine(m_shapes[TRI2]->vertex(0).x, m_shapes[TRI2]->vertex(0).y, m_shapes[TRI2]->vertex(1).x, m_shapes[TRI2]->vertex(1).y);
    memDC.DrawLine(m_shapes[TRI2]->vertex(1).x, m_shapes[TRI2]->vertex(1).y, m_shapes[TRI2]->vertex(2).x, m_shapes[TRI2]->vertex(2).y);
    memDC.DrawLine(m_shapes[TRI2]->vertex(2).x, m_shapes[TRI2]->vertex(2).y, m_shapes[TRI2]->vertex(0).x, m_shapes[TRI2]->vertex(0).y);
}

const float& Star::radius() const
{
    return m_shapes[TRI1]->radius();
}
