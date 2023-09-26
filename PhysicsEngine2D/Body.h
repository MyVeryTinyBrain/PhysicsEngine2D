#pragma once
#ifndef __Body_h__
#define __Body_h__

#include "Math.h"
#include "MemoryDC.h"

class Shape;

class Body
{
protected:
	size_t m_shapeCount;
	Shape** m_shapes;

	float m_mass;
	float m_invMass;
	float m_elasticity;
	float m_friction;
	float m_angularFriction;

	Vector2 m_velocity;
	float m_angularVelocity;

public:
	Body(size_t shapeCount);
	Body(size_t shapeCount, Shape* shapes...);
	virtual ~Body();

	virtual const Vector2& position() const = 0;
	virtual void setPosition(const Vector2& position) = 0;
	virtual const float& angle() const = 0;
	virtual void setAngle(const float& angle) = 0;

	virtual float inertia() const = 0;
	virtual void Draw(MemoryDC& memDC) const = 0;

	const size_t& shapeCount() const;
	Shape* shape(size_t index);

	const float& mass() const;
	void setMass(const float& mass);
	const float& invMass() const;
	void setInvMass(const float& invMass);
	float invInertia() const;
	const float& elastisity() const;
	void setElastisity(const float& elastisity);
	const float& friction() const;
	void setFriction(const float& friction);
	const float& angularFriction() const;
	void setAngularFriction(const float& friction);

	const Vector2& velocity() const;
	void setVelocity(const Vector2& velocity);
	const float& angularVelcoity() const;
	void setAngularVelocity(const float& angularVelocity);

	void Reposition();

	bool player = false;
};

#endif
