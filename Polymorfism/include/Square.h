#pragma once
#include "Shape.h";

class Square : public Shape {
public:
	Square(const Point2D &lowerLeftVertex, double sideLength);
	double area() const override;
	std::string toJSON() const override;

private:
	static const char* const s_typeName;
	static const char* const s_verticesName;
	static const char* const s_shapeName;
	static const size_t m_numOfVertices = 4;
	Point2D m_lowerLeftVertex{ 0,0 };
	double m_sideLenght{ 0 };
};