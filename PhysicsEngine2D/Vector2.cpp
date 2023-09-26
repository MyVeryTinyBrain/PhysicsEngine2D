#include "stdafx.h"
#include "Vector2.h"
#include <math.h>
#include "MathUtility.h"

Vector2::Vector2() : Vector2(0, 0)
{}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{}

Vector2 Vector2::operator+(const Vector2 & rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2 Vector2::operator*(const float& rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

Vector2& Vector2::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2 Vector2::operator/(const float& rhs) const
{
	return Vector2(x / rhs, y / y / rhs);
}

Vector2& Vector2::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	return !(*this == rhs);
}

float Vector2::magnitude() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::sqrMagnitude() const
{
	return x * x + y * y;
}

float Vector2::length() const
{
	return magnitude();
}

Vector2 Vector2::normalized() const
{
	float sqrLen = sqrMagnitude();
	if (sqrLen == 0) return Vector2::zero();
	float len = sqrtf(sqrLen);
	return Vector2(x / len, y / len);
}

void Vector2::Normalize()
{
	*this = normalized();
}

Vector2 Vector2::normal() const
{
	return Vector2(-y, x).normalized();
}

Vector2 Vector2::zero()
{
	return Vector2();
}

Vector2 Vector2::one()
{
	return Vector2(1, 1);
}

Vector2 Vector2::left()
{
	return Vector2(-1, 0);
}

Vector2 Vector2::right()
{
	return Vector2(1, 0);
}

Vector2 Vector2::up()
{
	return Vector2(0, 1);
}

Vector2 Vector2::down()
{
	return Vector2(0, -1);
}

Vector2 Vector2::upLeft()
{
	return Vector2(-1, 1);
}

Vector2 Vector2::upRight()
{
	return Vector2(1, 1);
}

Vector2 Vector2::downLeft()
{
	return Vector2(-1, -1);
}

Vector2 Vector2::downRight()
{
	return Vector2(1, -1);
}

float Vector2::Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

float Vector2::CrossZ(const Vector2 a, const Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

float Vector2::Cos(const Vector2& from, const Vector2& to)
{
	return Dot(from, to) / (from.magnitude() * to.magnitude());
}

float Vector2::Radian(const Vector2& from, const Vector2& to)
{
	Vector2 delta = to - from;
	if (delta.y > 0) return acosf(Cos(from, to));
	else return 2.0f * PI - acosf(Cos(from, to));
}

float Vector2::Angle(const Vector2& from, const Vector2& to)
{
	return Radian(from, to) * RAD2DEG;
}

Vector2 Vector2::Project(const Vector2& from, const Vector2& to)
{
	return (Dot(from, to) / Dot(to, to)) * to;
}

Vector2 Vector2::Proj(const Vector2& u, const Vector2& v)
{
	return (Dot(u, v) / Dot(u, u)) * u;
}

Vector2 Vector2::Perp(const Vector2& u, const Vector2& v)
{
	return v - Proj(u, v);
}

Vector2 Vector2::Reflect(const Vector2& normal, const Vector2& vector)
{
	const Vector2& v = vector;
	const Vector2& n = normal;
	return v - 2 * Dot(v, n) * n;
}

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, const float& t)
{
	return start + (end - start) * t;
}

Vector2 Vector2::InvLerp(const Vector2& start, const Vector2& end, const Vector2& v)
{
	float tx = (v.x - start.x) / (end.x - start.x);
	float ty = (v.y - start.y) / (end.y - start.y);
	return Vector2(tx, ty);
}

Vector2 Vector2::Direction(const float& radian)
{
	return Vector2(cosf(radian), sinf(radian));
}

Vector2 operator*(const float& lhs, const Vector2& rhs)
{
	return Vector2(rhs.x * lhs, rhs.y * lhs);
}
