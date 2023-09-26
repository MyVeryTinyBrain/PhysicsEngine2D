#pragma once
#ifndef __Wall_h__
#define __Wall_h__

#include "Body.h"

class Wall : public Body
{
public:
	Wall(float x1, float y1, float x2, float y2);
	Wall(Vector2 start, Vector2 end);
	virtual ~Wall();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& angle) override;

	virtual float inertia() const override;
	virtual void Draw(MemoryDC& memDC) const override;
};

#endif