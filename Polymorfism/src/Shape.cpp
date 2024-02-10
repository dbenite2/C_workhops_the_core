#include "Shape.h";

uint64_t Shape::s_nextID = 0u;
const char* const Shape::s_idName = "id";
const char* const Shape::s_areaName = "area";

Shape::Shape() : m_id(Shape::s_nextID++) {}
