#pragma once
#ifndef __Shape_h__
#define __Shape_h__

#include "Math.h"

class Shape
{
protected:
	size_t m_vertexCount;
	Vector2* m_vertices;
	float m_radius;
	Vector2 m_position;
	float m_angle; // radian

public:
	Shape(const size_t& vertexCount);
	virtual ~Shape();

	virtual const Vector2& position() const = 0;
	virtual void setPosition(const Vector2& position) = 0;
	virtual const float& angle() const = 0; // radian
	virtual void setAngle(const float& radian) = 0; // radian

	const Vector2& vertex(const size_t& index);
	const size_t& vertexCount() const;
	const float& radius() const;
	void setRadius(const float& radius);
};

#endif
