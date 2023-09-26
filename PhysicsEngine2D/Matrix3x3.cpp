#include "stdafx.h"
#include "Matrix3x3.h"

Matrix3x3::Matrix3x3() :
	m00(0), m01(0), m02(0),
	m10(0), m11(0), m12(0),
	m20(0), m21(0), m22(0)
{
}

Matrix3x3::Matrix3x3(float M00, float M01, float M02, float M10, float M11, float M12, float M20, float M21, float M22) :
	m00(M00), m01(M01), m02(M02),
	m10(M10), m11(M11), m12(M12),
	m20(M20), m21(M21), m22(M22)
{}

Vector3 Matrix3x3::row0() const
{
	return Vector3(m00, m01, m02);
}

Vector3 Matrix3x3::row1() const
{
	return Vector3(m10, m11, m12);
}

Vector3 Matrix3x3::row2() const
{
	return Vector3(m20, m21, m22);
}

Vector3 Matrix3x3::col0() const
{
	return Vector3(m00, m10, m20);
}

Vector3 Matrix3x3::col1() const
{
	return Vector3(m01, m11, m21);
}

Vector3 Matrix3x3::col2() const
{
	return Vector3(m02, m12, m22);
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 & rhs) const
{
	return Matrix3x3(
		m00 + rhs.m00, m01 + rhs.m01, m01 + rhs.m02,
		m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12,
		m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22
	);
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& rhs)
{
	m00 += rhs.m00; m01 += rhs.m01; m01 += rhs.m02;
	m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12;
	m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22;
	return *this;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& rhs) const
{
	return Matrix3x3(
		m00 - rhs.m00, m01 - rhs.m01, m01 - rhs.m02,
		m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12,
		m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22
	);
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& rhs)
{
	m00 -= rhs.m00; m01 -= rhs.m01; m01 -= rhs.m02;
	m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12;
	m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22;
	return *this;
}

Matrix3x3 Matrix3x3::operator*(const float& rhs) const
{
	return Matrix3x3(
		m00 * rhs, m01 * rhs, m01 * rhs,
		m10 * rhs, m11 * rhs, m12 * rhs,
		m20 * rhs, m21 * rhs, m22 * rhs
	);
}

Matrix3x3& Matrix3x3::operator*=(const float& rhs)
{
	m00*= rhs; m01*= rhs; m01*= rhs;
	m10*= rhs; m11*= rhs; m12*= rhs;
	m20*= rhs; m21*= rhs; m22*= rhs;
	return *this;
}

Vector3 Matrix3x3::operator*(const Vector3& rhs) const
{
	float x = Vector3::Dot(row0(), rhs);
	float y = Vector3::Dot(row1(), rhs);
	float z = Vector3::Dot(row2(), rhs);
	return Vector3(x, y, z);
}

Vector2 Matrix3x3::operator*(const Vector2& rhs) const
{
	Vector3 vector3(rhs.x, rhs.y, 1);
	Vector3 result = (*this) * vector3;
	return ToVector2(result);
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs)
{
	m00 = Vector3::Dot(row0(), rhs.col0());
	m01 = Vector3::Dot(row0(), rhs.col1());
	m02 = Vector3::Dot(row0(), rhs.col2());
	m10 = Vector3::Dot(row1(), rhs.col0());
	m11 = Vector3::Dot(row1(), rhs.col1());
	m12 = Vector3::Dot(row1(), rhs.col2());
	m20 = Vector3::Dot(row2(), rhs.col0());
	m21 = Vector3::Dot(row2(), rhs.col1());
	m22 = Vector3::Dot(row2(), rhs.col2());
	return *this;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& rhs) const
{
	float m00 = Vector3::Dot(row0(), rhs.col0());
	float m01 = Vector3::Dot(row0(), rhs.col1());
	float m02 = Vector3::Dot(row0(), rhs.col2());
	float m10 = Vector3::Dot(row1(), rhs.col0());
	float m11 = Vector3::Dot(row1(), rhs.col1());
	float m12 = Vector3::Dot(row1(), rhs.col2());
	float m20 = Vector3::Dot(row2(), rhs.col0());
	float m21 = Vector3::Dot(row2(), rhs.col1());
	float m22 = Vector3::Dot(row2(), rhs.col2());
	return Matrix3x3(m00, m01, m02, m10, m11, m12, m20, m21, m22);
}

Matrix3x3 Matrix3x3::Identity()
{
	Matrix3x3 zero;
	zero.m00 = 1;
	zero.m11 = 1;
	zero.m22 = 1;
	return zero;
}

Matrix3x3 Matrix3x3::Translate(float x, float y)
{
	return Matrix3x3(
		1, 0, x,
		0, 1, y,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::Rotate(float radian)
{
	float c = cosf(radian);
	float s = sinf(radian);
	return Matrix3x3(
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::Scale(float x, float y)
{
	return Matrix3x3(
		x, 0, 0,
		0, y, 0,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::TRS(const Vector2& position, const float& angle, const Vector2& size)
{
	return Translate(position.x, position.y) * Rotate(angle) * Scale(size.x, size.y);
}

Matrix3x3 operator*(const float& lhs, const Matrix3x3& rhs)
{
	return Matrix3x3(
		rhs.m00 * lhs, rhs.m01 * lhs, rhs.m01 * lhs,
		rhs.m10 * lhs, rhs.m11 * lhs, rhs.m12 * lhs,
		rhs.m20 * lhs, rhs.m21 * lhs, rhs.m22 * lhs
	);
}
