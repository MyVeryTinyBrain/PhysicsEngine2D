#include "stdafx.h"
#include "Shape.h"
#include <cassert>

Shape::Shape(const size_t& vertexCount) :
	m_vertexCount(vertexCount),
	m_vertices(new Vector2[vertexCount]{}),
	m_radius(0),
	m_position({}),
	m_angle(0)
{

}

Shape::~Shape()
{
	delete[] m_vertices;
}

const Vector2& Shape::vertex(const size_t& index)
{
	assert(index >= 0);
	assert(index < m_vertexCount);
	return m_vertices[index];
}

const size_t& Shape::vertexCount() const
{
	return m_vertexCount;
}

const float& Shape::radius() const
{
	return m_radius;
}

void Shape::setRadius(const float& radius)
{
	m_radius = radius;
}
