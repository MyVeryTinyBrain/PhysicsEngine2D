#pragma once
#ifndef __Circle_h__
#define __Circle_h__

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(const float& x, const float& y, const float& radius);
	Circle(const Vector2& position, const float& radius);
	virtual ~Circle();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& radian) override;
};

#endif
