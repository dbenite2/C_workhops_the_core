#include "AutoTest.h"

bool AutoTest::init(size_t argc, const char* argv[])
{
	return true;
}

void AutoTest::addCommentary(const std::string& exerciseName, const std::string& comment)
{
	ExerciseReport& report = m_reports[exerciseName];
	report.comments.push_back(comment);
}

void AutoTest::setMark(const std::string& exerciseName, double mark)
{
	ExerciseReport& report = m_reports[exerciseName];
	report.mark = mark;
}

void AutoTest::writeReportToConsole() const
{
	for(const auto& exerciseReportEntry : m_reports)
	{
		const std::string& exerciseName = exerciseReportEntry.first;
		const ExerciseReport& exerciseReport = exerciseReportEntry.second;
		std::string comments = "";
		if (exerciseReport.comments.empty())
		{
			comments += "- Felicidades, tu codigo pasa todos los tests automaticos, sigue asi";
		}
		else
		{
			for (const std::string& comment : exerciseReport.comments)
			{
				comments += ("- " + comment + "\n");
			}
		}
		std::cout << "Resultado de ejecutar los tests automaticos: " << std::endl;
		std::cout << comments << std::endl;
	}
}