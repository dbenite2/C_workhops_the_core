#include "Square.h"
#include "JSONBuilder.h";

const char* const Square::s_typeName{ "type" };
const char* const Square::s_verticesName{ "vertices" };
const char* const Square::s_shapeName{ "square" };

Square::Square(const Point2D &lowerLeftVertex, double sideLength):
	m_lowerLeftVertex(lowerLeftVertex), m_sideLenght(sideLength) {
}

double Square::area() const {
	return m_sideLenght * m_sideLenght;
}

std::string Square::toJSON() const {
	JSONBuilder builder;
	builder.startObject();
	builder.writeInt(s_idName, m_id, true);
	builder.writeCString(s_typeName, s_shapeName, true);
	builder.startArray(s_verticesName);

	Point2D vertices[4] = {
		m_lowerLeftVertex,
		{m_lowerLeftVertex.x + m_sideLenght, m_lowerLeftVertex.y},
		{m_lowerLeftVertex.x + m_sideLenght, m_lowerLeftVertex.y + m_sideLenght},
		{m_lowerLeftVertex.x, m_lowerLeftVertex.y + m_sideLenght}
	};

	for (int i = 0; i < 4; i++) {
		std::stringstream vertex;
		vertex << "[" << vertices[i].x << ", " << vertices[i].y << "]";
		builder.addArrayElement(vertex.str(), i == 0, i < 3);
	}
	builder.endArray(true);
	builder.writeDouble(s_areaName, area(), false);
	builder.endObject();

	return builder.build();
}

