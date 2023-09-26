#pragma once
#ifndef __Capsule_h__
#define __Capsule_h__

#include "Body.h"

class Capsule : public Body
{
public:
	Capsule(Vector2 start, Vector2 end, float r);
	virtual ~Capsule();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& angle) override;

	virtual float inertia() const override;
	virtual void Draw(MemoryDC& memDC) const override;

	const float& radius() const;
	const Vector2& start() const;
	const Vector2& end() const;
};

#endif
