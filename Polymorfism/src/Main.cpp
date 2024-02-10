#include <iostream>
#include "Triangle.h";
#include "Circle.h";
#include "Square.h";
#include <array>;
#include <thread>;
#include <chrono>

//#include "Singleton.h";

int main() {


	constexpr size_t arraySize = 50000000;
	std::array<int, arraySize> input{};
	// ... inicializamos el contenido de input ...
	auto f = [](std::array<int, arraySize>& input, size_t start, size_t end) {
			for (size_t i = start; i <= end; i++)
			{
				input[i] *= 2;
			}
	};

	std::thread threadMain(f, std::ref(input), 0, arraySize - 1);
	std::thread thread1(f, std::ref(input), 0, arraySize / 2);
	std::thread thread2(f, std::ref(input), (arraySize / 2) + 1, arraySize - 1);
	auto mainBefore = std::chrono::high_resolution_clock::now();
	threadMain.join();
	auto mainAfter = std::chrono::high_resolution_clock::now();

	auto before = std::chrono::high_resolution_clock::now();
	thread1.join(); // esperamos a que el thread1 termine
	thread2.join(); // esperamos a que el thread2 termine
	auto after = std::chrono::high_resolution_clock::now();

	const std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
	const std::chrono::milliseconds deltaMain = std::chrono::duration_cast<std::chrono::milliseconds>(mainAfter - mainBefore);
	std::cout << delta.count() << std::endl;
	std::cout << "Time elapsed on one thread: " << deltaMain.count() << "ms" << std::endl;

	/*Point2D a{ 1.1,2.1 };
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
	}*/

	//Circle* singletonPTR = Singleton<Circle>::getInstance();

	return 0;
}