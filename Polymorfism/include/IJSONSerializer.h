#pragma once
#include <string>;

class IJSONSerializer {
public:
	virtual std::string toJSON() const = 0;
	virtual ~IJSONSerializer() {}
};
