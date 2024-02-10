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

	Point2D vertices[m_numOfVertices] = {
		m_lowerLeftVertex,
		{m_lowerLeftVertex.x + m_sideLenght, m_lowerLeftVertex.y},
		{m_lowerLeftVertex.x + m_sideLenght, m_lowerLeftVertex.y + m_sideLenght},
		{m_lowerLeftVertex.x, m_lowerLeftVertex.y + m_sideLenght}
	};

	for (size_t i = 0; i < m_numOfVertices; i++) {
		builder.addArrayElement(vertices[i].x, vertices[i].y, i, i < m_numOfVertices - 1);
	}
	builder.endArray(true);
	builder.writeDouble(s_areaName, area(), false);
	builder.endObject();

	return builder.build();
}

