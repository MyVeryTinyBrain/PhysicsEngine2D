#pragma once
#ifndef __Vector3_h__
#define __Vector3_h__

struct Vector3
{
	float x, y, z;
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3 operator +(const Vector3& rhs) const;
	Vector3& operator +=(const Vector3& rhs);
	Vector3 operator -(const Vector3& rhs) const;
	Vector3& operator -=(const Vector3& rhs);
	Vector3 operator *(const float& rhs) const;
	Vector3& operator *=(const float& rhs);
	Vector3 operator /(const float& rhs) const;
	Vector3& operator /=(const float& rhs);
	bool operator == (const Vector3& rhs) const;
	bool operator != (const Vector3& rhs) const;
	float magnitude() const;
	float sqrMagnitude() const;
	float length() const;
	Vector3 normalized() const;
	void Normalize();
	static Vector3 zero();
	static Vector3 one();
	static float Dot(const Vector3& a, const Vector3& b);
	static Vector3 Cross(const Vector3 a, const Vector3& b);
	static float Cos(const Vector3& from, const Vector3& to);
	static float Radian(const Vector3& from, const Vector3& to);
	static float Angle(const Vector3& from, const Vector3& to);
	static Vector3 Project(const Vector3& from, const Vector3& to);
	static Vector3 Proj(const Vector3& u, const Vector3& v);
	static Vector3 Perp(const Vector3& u, const Vector3& v);
	static Vector3 Reflect(const Vector3& normal, const Vector3& vector);
	static Vector3 Lerp(const Vector3& start, const Vector3& end, const float& t);
	static Vector3 InvLerp(const Vector3& start, const Vector3& end, const Vector3& v);
};

Vector3 operator * (const float& lhs, const Vector3& rhs);

#endif