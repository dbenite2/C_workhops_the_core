#pragma once
#include "Point2D.h";
#include "IJSONSerializer.h";

class Shape : public IJSONSerializer {
public:
	Shape();
	virtual ~Shape() {};
	virtual double area() const = 0;
protected:
	uint64_t m_id {0};
	static uint64_t s_nextID;
	std::string m_type;
	static const char* const s_idName;
	static const char* const s_areaName;

};
