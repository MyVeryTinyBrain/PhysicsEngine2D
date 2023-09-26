#include "stdafx.h"
#include "Body.h"
#include "Shape.h"
#include <cstdarg>
#include <cassert>

Body::Body(size_t shapeCount) :
	m_shapeCount(shapeCount),
	m_shapes(new Shape* [shapeCount]),
	m_mass(1),
	m_invMass(1),
	m_elasticity(0.9f),
	m_friction(0.1f),
	m_angularFriction(0.01f),
	m_velocity({ 0,0 }),
	m_angularVelocity(0)
{
}

Body::Body(size_t shapeCount, Shape* shapes...) :
	m_shapeCount(shapeCount),
	m_shapes(new Shape* [shapeCount]) ,
	m_mass(0),
	m_invMass(0),
	m_elasticity(0),
	m_friction(0),
	m_angularFriction(0),
	m_velocity({0,0}),
	m_angularVelocity(0)
{
	if (shapeCount > 0)
	{
		assert(shapes != nullptr);
		va_list ap;
		va_start(ap, shapes);
		Shape* shape = shapes;
		for (size_t i = 0; i < shapeCount; ++i)
		{
			assert(shape != nullptr);
			m_shapes[i] = shape;
			shape = va_arg(ap, Shape*);
		}
		va_end(ap);
	}
}

Body::~Body()
{
	for (size_t i = 0; i < m_shapeCount; ++i)
		delete m_shapes[i];
	delete[] m_shapes;
}

const size_t& Body::shapeCount() const
{
	return m_shapeCount;
}

Shape* Body::shape(size_t index)
{
	return m_shapes[index];
}

const float& Body::mass() const
{
	return m_mass;
}

void Body::setMass(const float& mass)
{
	m_mass = mass;
	if (mass == 0) m_invMass = 0;
	else m_invMass = 1.0f / mass;
}

const float& Body::invMass() const
{
	return m_invMass;
}

void Body::setInvMass(const float& invMass)
{
	m_invMass = invMass;
	if (invMass == 0) m_mass = 0;
	else m_mass = 1.0f / invMass;
}

float Body::invInertia() const
{
	float _inertia = inertia();
	if (_inertia == 0) return 0;
	else return 1.0f / _inertia;
}

const float& Body::elastisity() const
{
	return m_elasticity;
}

void Body::setElastisity(const float& elastisity)
{
	m_elasticity = elastisity;
}

const float& Body::friction() const
{
	return m_friction;
}

void Body::setFriction(const float& friction)
{
	m_friction = friction;
}

const float& Body::angularFriction() const
{
	return m_angularFriction;
}

void Body::setAngularFriction(const float& friction)
{
	m_angularFriction = friction;
}

const Vector2& Body::velocity() const
{
	return m_velocity;
}

void Body::setVelocity(const Vector2& velocity)
{
	m_velocity = velocity;
}

const float& Body::angularVelcoity() const
{
	return m_angularVelocity;
}

void Body::setAngularVelocity(const float& angularVelocity)
{
	m_angularVelocity = angularVelocity;
}

void Body::Reposition()
{
	setPosition(position() + m_velocity);
	setAngle(angle() + m_angularVelocity);
	m_velocity *= (1.0f - m_friction);
	m_angularVelocity *= (1.0f - m_angularFriction);
}
