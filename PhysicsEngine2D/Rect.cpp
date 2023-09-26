#include "stdafx.h"
#include "Rect.h"

#define LT	0
#define RT	1
#define RB	2
#define LB	3

Rect::Rect(const float& left, const float& top, const float& right, const  float& bottom) : Shape(4)
{
	m_vertices[LT] = { left, top };
	m_vertices[RT] = { right, top };
	m_vertices[RB] = { right, bottom };
	m_vertices[LB] = { left, bottom };
	Init();
}

Rect::Rect(const Vector2& leftTop, const Vector2& rightBottom) : Shape(4)
{
	m_vertices[LT] = leftTop;
	m_vertices[RT] = { rightBottom.x, leftTop.y };
	m_vertices[RB] = rightBottom;
	m_vertices[LB] = { leftTop.x, rightBottom.y };
	Init();
}

Rect::Rect(const Vector2& leftTop, const Vector2& rightTop, const float& height) : Shape(4)
{
	m_vertices[LT] = leftTop;
	m_vertices[RT] = rightTop;
	Vector2 rel = leftTop - rightTop;
	Vector2 dir = rel.normalized();
	Vector2 nor = dir.normal();
	m_vertices[LB] = leftTop + nor * height;
	m_vertices[RB] = rightTop + nor * height;
	Init();
}

Rect::Rect(const float& width, const Vector2& leftTop, const Vector2& leftBottom) : Shape(4)
{
	m_vertices[LT] = leftTop;
	m_vertices[LB] = leftBottom;
	Vector2 rel = leftBottom - leftTop;
	Vector2 dir = rel.normalized();
	Vector2 nor = dir.normal();
	m_vertices[RT] = leftTop + nor * width;
	m_vertices[RB] = leftBottom + nor * width;
	Init();
}

Rect::~Rect()
{
}

const Vector2& Rect::position() const
{
	return m_position;
}

void Rect::setPosition(const Vector2& position)
{
	m_position = position;
	UpdateVertices();
}

const float& Rect::angle() const
{
	return m_angle;
}

void Rect::setAngle(const float& radian)
{
	m_angle = radian;
	UpdateVertices();
}

float Rect::width() const
{
	return (m_vertices[RT] - m_vertices[LT]).magnitude();
}

float Rect::height() const
{
	return (m_vertices[LT] - m_vertices[LB]).magnitude();
}

Vector2 Rect::horizontalDirection() const
{
	return (m_vertices[RT] - m_vertices[LT]).normalized();
}

Vector2 Rect::verticalDirection() const
{
	return (m_vertices[LT] - m_vertices[LB]).normalized();
}

void Rect::Init()
{
	m_position = (m_vertices[LT] + m_vertices[RB]) * 0.5f;
	m_originalVertices[LT] = m_vertices[LT] - m_position;
	m_originalVertices[RT] = m_vertices[RT] - m_position;
	m_originalVertices[RB] = m_vertices[RB] - m_position;
	m_originalVertices[LB] = m_vertices[LB] - m_position;
}

void Rect::UpdateVertices()
{
	Matrix3x3 R = Matrix3x3::Rotate(m_angle);
	Matrix3x3 T = Matrix3x3::Translate(+m_position.x, +m_position.y);
	Matrix3x3 M = T * R;
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		m_vertices[i] = M * m_originalVertices[i];
	}
}
