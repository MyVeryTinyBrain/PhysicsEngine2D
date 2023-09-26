#pragma once
#ifndef __RegularPolygoneShape_h__
#define __RegularPolygoneShape_h__

#include "Shape.h"

class RegularPolygonShape : public Shape
{
	float m_begAngle;
public:
	RegularPolygonShape(float x, float y, float length, float begAngle, size_t n);
	RegularPolygonShape(Vector2 position, float length, float begAngle, size_t n);
	virtual ~RegularPolygonShape();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& radian) override;

	const float& length() const;

private:
	void UpdateVertices();
};

#endif
