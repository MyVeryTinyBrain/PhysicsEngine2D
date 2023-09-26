#pragma once
#ifndef __Line_h__
#define __Line_h__

#include "Shape.h"

class Line : public Shape
{
	Vector2 m_direction;
	float m_length;

public:
	Line(const float& x1, const float& y1, const float& x2, const float& y2);
	Line(const Vector2& p1, const Vector2& p2);
	virtual ~Line();

	const Vector2& direction() const; // from start to end
	void setDirection(const Vector2& direction);
	const float& length() const;
	void setLength(const float& length);
	const Vector2& start() const;
	const Vector2& end() const;

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override; // radian
	virtual void setAngle(const float& radian) override; // radian

private:
	void UpdateVertices();
};

#endif
