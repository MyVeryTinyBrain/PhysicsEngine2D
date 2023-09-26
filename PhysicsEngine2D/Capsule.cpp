#include "stdafx.h"
#include "Capsule.h"
#include "Rect.h"
#include "Circle.h"

#define CIRCLE1		0
#define CIRCLE2		2
#define RECT		1

Capsule::Capsule(Vector2 start, Vector2 end, float r) : Body(3)
{
	m_shapes[CIRCLE1] = new Circle(start, r);
	m_shapes[CIRCLE2] = new Circle(end, r);
	Vector2 rel = end - start;
	Vector2 dir = rel.normalized();
	Vector2 nor = dir.normal();
	Vector2 leftTop = start + nor * r;
	Vector2 rightTop = end + nor * r;
	m_shapes[RECT] = new Rect(leftTop, rightTop, r * 2);
}

Capsule::~Capsule()
{
}

const Vector2& Capsule::position() const
{
	return m_shapes[RECT]->position();
}

void Capsule::setPosition(const Vector2& position)
{
	Rect* rect = static_cast<Rect*>(m_shapes[RECT]);
	rect->setPosition(position);

	Vector2 center = rect->position();
	Vector2 dir = rect->horizontalDirection();
	const float& width = rect->width();
	Vector2 start = center - dir * width * 0.5f;
	Vector2 end = center + dir * width * 0.5f;
	m_shapes[CIRCLE1]->setPosition(start);
	m_shapes[CIRCLE2]->setPosition(end);
}

const float& Capsule::angle() const
{
	return m_shapes[RECT]->angle();
}

void Capsule::setAngle(const float& angle)
{
	Rect* rect = static_cast<Rect*>(m_shapes[RECT]);
	rect->setAngle(angle);

	Vector2 center = rect->position();
	Vector2 dir = rect->horizontalDirection();
	const float& width = rect->width();
	Vector2 start = center - dir * width * 0.5f;
	Vector2 end = center + dir * width * 0.5f;
	m_shapes[CIRCLE1]->setPosition(start);
	m_shapes[CIRCLE2]->setPosition(end);
}

float Capsule::inertia() const
{
	Circle* circle1 = static_cast<Circle*>(m_shapes[CIRCLE1]);
	Rect* rect = static_cast<Rect*>(m_shapes[RECT]);
	float r = circle1->radius();
	float width = rect->width();
	float length = 2 * r + width;
	return (m_mass * length * length) / 12.0f;
}

void Capsule::Draw(MemoryDC& memDC) const
{
	Circle* circle1 = static_cast<Circle*>(m_shapes[CIRCLE1]);
	Circle* circle2 = static_cast<Circle*>(m_shapes[CIRCLE2]);
	Rect* rect = static_cast<Rect*>(m_shapes[RECT]);
	const Vector2& c1 = circle1->position();
	const float& r1 = circle1->radius();
	const Vector2& c2 = circle2->position();
	const float& r2 = circle2->radius();
	const Vector2& p1 = rect->vertex(0);
	const Vector2& p2 = rect->vertex(1);
	const Vector2& p3 = rect->vertex(2);
	const Vector2& p4 = rect->vertex(3);
	memDC.SetBrush(MemoryBrush::MakeNullBrush());
	memDC.SetPen(0, 255, 0, 1);
	memDC.DrawCircle(c1.x, c1.y, r1);
	memDC.DrawCircle(c2.x, c2.y, r2);
	memDC.DrawLine(p1.x, p1.y, p2.x, p2.y);
	memDC.DrawLine(p2.x, p2.y, p3.x, p3.y);
	memDC.DrawLine(p3.x, p3.y, p4.x, p4.y);
	memDC.DrawLine(p4.x, p4.y, p1.x, p1.y);
}

const float& Capsule::radius() const
{
	Circle* circle1 = static_cast<Circle*>(m_shapes[CIRCLE1]);
	return circle1->radius();
}

const Vector2& Capsule::start() const
{
	Circle* circle1 = static_cast<Circle*>(m_shapes[CIRCLE1]);
	return circle1->position();
}

const Vector2& Capsule::end() const
{
	Circle* circle2 = static_cast<Circle*>(m_shapes[CIRCLE2]);
	return circle2->position();
}
