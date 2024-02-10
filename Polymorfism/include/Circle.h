#pragma once
#include "Shape.h";

class Circle : public Shape {
public:
	Circle(const Point2D& point, double radius);
	double area() const override;
	std::string toJSON() const override;

private:
	static const char* const s_typeName;
	static const char* const s_verticesName;
	static const char* const s_shapeName;
	Point2D m_center{ 0,0 };
	double m_radius{ 0 };
};
