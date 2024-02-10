#include <cmath>;
#include "Triangle.h";
#include "JSONBuilder.h";

const char* const Triangle::s_typeName = "type";
const char* const Triangle::s_verticesName = "vertices";
const char* const Triangle::s_shapeName = "triangle";

Triangle::Triangle(const Point2D& v1, const Point2D& v2, const Point2D& v3) :
	m_vertices{ v1,v2,v3 } {
}

double Triangle::area() const {
	return std::abs((m_vertices[0].x * (m_vertices[1].y - m_vertices[2].y) +
		m_vertices[1].x * (m_vertices[2].y - m_vertices[1].y) +
		m_vertices[2].x * (m_vertices[0].y - m_vertices[1].y)) / 2);
}

std::string Triangle::toJSON() const {

	JSONBuilder builder;
	builder.startObject();
	builder.writeInt(s_idName, m_id, true);
	builder.writeCString(s_typeName, s_shapeName, true);
	builder.startArray(s_verticesName);
	for (int i = 0; i < 3; i++) {
		std::stringstream vertex;
		vertex << "[" << m_vertices[i].x << ", " << m_vertices[i].y << "]";
		builder.addArrayElement(vertex.str(),i == 0, i < 2);
	}
	builder.endArray(true);
	builder.writeDouble(s_areaName, area(), false);
	builder.endObject();
    
	return builder.build();
}

