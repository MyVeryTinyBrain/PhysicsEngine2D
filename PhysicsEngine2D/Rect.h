#pragma once
#ifndef __Rectangle_h__
#define __Rectangle_h__

#include "Shape.h"

class Rect : public Shape
{
	Vector2 m_originalVertices[4];

public:
	Rect(const float& left, const float& top, const float& right, const float& bottom);
	Rect(const Vector2& leftTop, const Vector2& rightBottom);
	Rect(const Vector2& leftTop, const Vector2& rightTop, const float& height);
	Rect(const float& width, const Vector2& leftTop, const Vector2& leftBottom);
	virtual ~Rect();

	virtual const Vector2& position() const override;
	virtual void setPosition(const Vector2& position) override;
	virtual const float& angle() const override;
	virtual void setAngle(const float& radian) override;

	float width() const;
	float height() const;
	Vector2 horizontalDirection() const; // from left to right
	Vector2 verticalDirection() const; // from down to up

private:
	void Init();
	void UpdateVertices();
};

#endif
