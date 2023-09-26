#pragma once
#ifndef __Vector_h__
#define __Vector_h__

#include "Vector2.h"
#include "Vector3.h"

inline Vector2 ToVector2(const Vector3& vector3)
{
	return Vector2(vector3.x, vector3.y);
}

inline Vector3 ToVector3(const Vector2& vector2)
{
	return Vector3(vector2.x, vector2.y, 0);
}

#endif