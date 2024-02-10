#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <numeric> // para std::accumulate
#include <iostream>

#define STRINGIFY(A) #A

#define START_TEST(argc, argv)																													\
	AutoTest autoTest;																															\
	bool ok = autoTest.init(argc, argv);																										\
	if(ok == false)																																\
	{																																			\
		std::cout << "AutoTest could not be initialized" << std::endl;																			\
		return 0;																																\
	}

#define START_EXERCISE(DateClass)																												\
	{																																			\
		const std::string exerciseName = STRINGIFY(DateClass);																					\
		std::list<double> testsMarks;																											\
		std::list<double>* currentMarksList = &testsMarks;																						\

#define START_COMPOSED_CHECK()																													\
	{																																			\
		std::list<double> composedTestMarks;																									\
		currentMarksList = &composedTestMarks;

#define END_COMPOSED_CHECK()																													\
		const double composedMark = std::accumulate(currentMarksList->begin(), currentMarksList->end(), 0.0) / std::size(*currentMarksList);	\
		testsMarks.push_back(composedMark);																										\
		currentMarksList = &testsMarks;																											\
	}

#define CHECK_EQUAL(p1, p2, message)																											\
		if(p1 == p2)																															\
		{																																		\
			currentMarksList->push_back(10.0);																									\
		}																																		\
		else																																	\
		{																																		\
			currentMarksList->push_back(0.0);																									\
			autoTest.addCommentary(exerciseName, message);																						\
		}

#define CHECK_NOT_EQUAL(p1, p2, message)																										\
		if(p1 != p2)																															\
		{																																		\
			currentMarksList->push_back(10.0);																									\
		}																																		\
		else																																	\
		{																																		\
			currentMarksList->push_back(0.0);																									\
			autoTest.addCommentary(exerciseName, message);																						\
		}

#define DISABLE_CHECK(message) \
		currentMarksList->push_back(0.0);																									    \
		autoTest.addCommentary(exerciseName, message);																							\

#define END_EXERCISE()																															\
		const double finalMark = std::accumulate(testsMarks.begin(), testsMarks.end(), 0.0) / std::size(testsMarks);							\
		autoTest.setMark(exerciseName, finalMark);																								\
	}

#define END_TEST() autoTest.writeReportToConsole();																									

#define UNUSED(expr) do { (void)(expr); } while (0)


struct ExerciseReport
{
	double mark;
	std::list<std::string> comments;
};

using ExercisesReports = std::unordered_map<std::string, ExerciseReport>;


class AutoTest
{
	public:

		AutoTest() = default;

		bool init(size_t argCount, const char* argValues[]);

		void addCommentary(const std::string& exerciseName, const std::string& comment);
		void setMark(const std::string& exerciseName, double mark);

		void writeReportToConsole() const;

	private:

		std::string			m_studentName{};
		std::string			m_csvFilePath{};
		ExercisesReports	m_reports{};
};