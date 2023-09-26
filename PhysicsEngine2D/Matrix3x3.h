#pragma once
#ifndef __Matrix3x3_h__
#define __Matrix3x3_h__

#include "Vector.h"
#include <math.h>

struct Matrix3x3
{
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;
	Matrix3x3();
	Matrix3x3(float M00, float M01, float M02, float M10, float M11, float M12, float M20, float M21, float M22);
	Vector3 row0() const;
	Vector3 row1() const;
	Vector3 row2() const;
	Vector3 col0() const;
	Vector3 col1() const;
	Vector3 col2() const;
	Matrix3x3 operator + (const Matrix3x3& rhs) const;
	Matrix3x3& operator += (const Matrix3x3& rhs);
	Matrix3x3 operator - (const Matrix3x3& rhs) const;
	Matrix3x3& operator -= (const Matrix3x3& rhs);
	Matrix3x3 operator * (const float& rhs) const;
	Matrix3x3& operator *= (const float& rhs);
	Vector3 operator * (const Vector3& rhs) const;
	Vector2 operator * (const Vector2& rhs) const;
	Matrix3x3& operator *= (const Matrix3x3& rhs);
	Matrix3x3 operator * (const Matrix3x3& rhs) const;
	static Matrix3x3 Identity();
	static Matrix3x3 Translate(float x, float y);
	static Matrix3x3 Rotate(float radian);
	static Matrix3x3 Scale(float x, float y);
	static Matrix3x3 TRS(const Vector2& position, const float& angle, const Vector2& size);
};

Matrix3x3 operator * (const float& lhs, const Matrix3x3& rhs);

#endif