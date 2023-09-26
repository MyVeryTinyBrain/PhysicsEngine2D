#pragma once
#ifndef __Box_h__
#define __Box_h__

#include "Body.h"

class Box : public Body
{
public:
	Box(Vector2 leftTop, Vector2 rightBottom);
	Box(float left, float top, float right, float bottom);
	Box(Vector2 leftTop, Vector2 rightTop, float height);
	Box(float width, Vector2 leftTop, Vector2 leftBottom);
	virtual ~Box();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& angle) override;

	virtual float inertia() const override;
	virtual void Draw(MemoryDC& memDC) const override;
};

#endif
