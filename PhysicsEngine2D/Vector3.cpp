#include "stdafx.h"
#include "Vector3.h"
#include <math.h>
#include "MathUtility.h"

Vector3::Vector3() : Vector3(0, 0, 0)
{
}

Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator*(const float& rhs) const
{
	return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3& Vector3::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector3 Vector3::operator/(const float& rhs) const
{
	return Vector3(x / rhs, y / y / rhs, z / rhs);
}

Vector3& Vector3::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool Vector3::operator!=(const Vector3& rhs) const
{
	return !(*this == rhs);
}

float Vector3::magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::sqrMagnitude() const
{
	return x * x + y * y + z * z;
}

float Vector3::length() const
{
	return magnitude();
}

Vector3 Vector3::normalized() const
{
	float sqrLen = sqrMagnitude();
	if (sqrLen == 0) return Vector3::zero();
	float len = sqrtf(sqrLen);
	return Vector3(x / len, y / len, z / len);
}

void Vector3::Normalize()
{
	*this = normalized();
}

Vector3 Vector3::zero()
{
	return Vector3();
}

Vector3 Vector3::one()
{
	return Vector3(1, 1, 1);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(const Vector3 a, const Vector3& b)
{
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	return Vector3(x, y, z);
}

float Vector3::Cos(const Vector3& from, const Vector3& to)
{
	return Dot(from, to) / (from.magnitude() * to.magnitude());
}

float Vector3::Radian(const Vector3& from, const Vector3& to)
{
	return acosf(Cos(from, to));
}

float Vector3::Angle(const Vector3& from, const Vector3& to)
{
	return Radian(from, to) * RAD2DEG;
}

Vector3 Vector3::Project(const Vector3& from, const Vector3& to)
{
	return (Dot(from, to) / Dot(to, to)) * to;
}

Vector3 Vector3::Proj(const Vector3& u, const Vector3& v)
{
	return (Dot(u, v) / Dot(u, u)) * u;
}

Vector3 Vector3::Perp(const Vector3& u, const Vector3& v)
{
	return v - Proj(u, v);
}

Vector3 Vector3::Reflect(const Vector3& normal, const Vector3& vector)
{
	const Vector3& v = vector;
	const Vector3& n = normal;
	return v - 2 * Dot(v, n) * n;
}

Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, const float& t)
{
	return start + (end - start) * t;
}

Vector3 Vector3::InvLerp(const Vector3& start, const Vector3& end, const Vector3& v)
{
	float tx = (v.x - start.x) / (end.x - start.x);
	float ty = (v.y - start.y) / (end.y - start.y);
	float tz = (v.z - start.z) / (end.z - start.z);
	return Vector3(tx, ty, tz);
}

Vector3 operator*(const float& lhs, const Vector3& rhs)
{
	return Vector3(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
}
