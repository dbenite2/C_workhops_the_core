#include <iostream>
#include "Triangle.h";
#include "Circle.h";
#include "Square.h";

int main() {

	Point2D a{ 1.1,2.1 };
	Point2D b{ 3.1,4.1 };
	Point2D c{ 5.1,6.1 };

	Shape* test[3] = { new Triangle(a, b, c), new Circle(a, 4.0), new Square(c, 4.0) };

	Circle newCircle(c, 3.5);

	for (int i = 0; i < 3; i++) {
		std::cout << test[i]->toJSON() << "," << std::endl;
	}

	std::cout << newCircle.toJSON() << std::endl;
	for (int i = 0; i < 3; i++) {
		delete test[i];
	}

	return 0;
}