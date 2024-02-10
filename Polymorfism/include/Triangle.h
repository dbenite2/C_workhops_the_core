#pragma once
#include "Shape.h";

class Triangle: public Shape {
public:
	Triangle(const Point2D& v1, const Point2D& v2, const Point2D& v3);
	double area() const override;
	std::string toJSON() const override;

private:
	static const char* const s_typeName;
	static const char* const s_verticesName;
	static const char* const s_shapeName;
	static const size_t m_numOfVertices = 3;
	Point2D m_vertices[m_numOfVertices] = { 0 };

};
