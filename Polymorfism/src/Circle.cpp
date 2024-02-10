#include <numbers>
#include "Circle.h"
#include "JSONBuilder.h";

const char* const Circle::s_typeName{ "type" };
const char* const Circle::s_verticesName{ "center" };
const char* const Circle::s_shapeName{ "circle" };

Circle::Circle(const Point2D &center, double radius):
	m_center(center), m_radius(radius)
{}

double Circle::area() const {
	return std::numbers::pi * m_radius * m_radius;
}

std::string Circle::toJSON() const {
	JSONBuilder builder;
	builder.startObject();
	builder.writeInt(s_idName, m_id, true);
	builder.writeCString(s_typeName, s_shapeName, true);
	builder.startArray(s_verticesName);
	builder.addArrayElement(m_center.x, m_center.y, 0, false);
	builder.endArray(true);
	builder.writeDouble(s_areaName, area(), false);
	builder.endObject();

	return builder.build();
}
