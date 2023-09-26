#pragma once
#ifndef __Vector2_h__
#define __Vector2_h__

struct Vector2
{
	float x, y;
	Vector2();
	Vector2(float _x, float _y);
	Vector2 operator +(const Vector2& rhs) const;
	Vector2& operator +=(const Vector2& rhs);
	Vector2 operator -(const Vector2& rhs) const;
	Vector2& operator -=(const Vector2& rhs);
	Vector2 operator *(const float& rhs) const;
	Vector2& operator *=(const float& rhs);
	Vector2 operator /(const float& rhs) const;
	Vector2& operator /=(const float& rhs);
	bool operator == (const Vector2& rhs) const;
	bool operator != (const Vector2& rhs) const;
	float magnitude() const;
	float sqrMagnitude() const;
	float length() const;
	Vector2 normalized() const;
	void Normalize();
	Vector2 normal() const; // Rotate 90 degrees
	static Vector2 zero();
	static Vector2 one();
	static Vector2 left();
	static Vector2 right();
	static Vector2 up();
	static Vector2 down();
	static Vector2 upLeft();
	static Vector2 upRight();
	static Vector2 downLeft();
	static Vector2 downRight();
	static float Dot(const Vector2& a, const Vector2& b);
	static float CrossZ(const Vector2 a, const Vector2& b);
	static float Cos(const Vector2& from, const Vector2& to);
	static float Radian(const Vector2& from, const Vector2& to);
	static float Angle(const Vector2& from, const Vector2& to);
	static Vector2 Project(const Vector2& from, const Vector2& to);
	static Vector2 Proj(const Vector2& u, const Vector2& v);
	static Vector2 Perp(const Vector2& u, const Vector2& v);
	static Vector2 Reflect(const Vector2& normal, const Vector2& vector);
	static Vector2 Lerp(const Vector2& start, const Vector2& end, const float& t);
	static Vector2 InvLerp(const Vector2& start, const Vector2& end, const Vector2& v);
	static Vector2 Direction(const float& radian);
};

Vector2 operator * (const float& lhs, const Vector2& rhs);

#endif