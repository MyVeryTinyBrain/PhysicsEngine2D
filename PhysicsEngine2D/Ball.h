#pragma once
#ifndef __Ball_h__
#define __Ball_h__

#include "Body.h"

class Ball : public Body
{
public:
	Ball(float x, float y, float r);
	virtual ~Ball();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& angle) override;

	virtual float inertia() const override;
	virtual void Draw(MemoryDC& memDC) const override;

	const float& radius() const;
};

#endif