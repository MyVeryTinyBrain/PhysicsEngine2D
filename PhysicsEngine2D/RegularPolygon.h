#pragma once
#ifndef __RegularPolygon_h__
#define __RegularPolygon_h__

#include "Body.h"

class RegularPolygon : public Body
{
public:
	RegularPolygon(float x, float y, float length, float begAngle, size_t n);
	RegularPolygon(Vector2 position, float length, float begAngle, size_t n);
	virtual ~RegularPolygon();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& angle) override;

	virtual float inertia() const override;
	virtual void Draw(MemoryDC& memDC) const override;

	const float& length() const; // = radius
	const float& radius() const; // = length
};

#endif
