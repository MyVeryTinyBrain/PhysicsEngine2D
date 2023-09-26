#pragma once
#ifndef __Star_h__
#define __Star_h__

#include "Body.h"

class Star : public Body
{
public:
	Star(float x, float y, float radius);
	Star(Vector2 position, float radius);
	virtual ~Star();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;

	virtual const float& angle() const override;
	virtual void setAngle(const float& angle) override;
	virtual float inertia() const override;
	virtual void Draw(MemoryDC& memDC) const override;

	const float& radius() const;
};

#endif
