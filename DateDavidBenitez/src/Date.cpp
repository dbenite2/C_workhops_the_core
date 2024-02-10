#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include "Date.h";

static const char* months[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

Date::Date(const int& day, const int& month, const int& year) : 
	m_day(day),
	m_month(month),
	m_year(year)
{
	if (!isValidDate(m_day, m_month, m_year)) {
		throw InvalidDate("Exception: The given dates are not valid");
	}
}
Date::Date(const char* dateFormat) {
	[[maybe_unused]] int result = sscanf(dateFormat, "%d/%d/%d", &m_year, &m_month, &m_day);
	if (!isValidDate(m_day, m_month, m_year)) {
		throw InvalidDate("Exception: The given string has invalid dates");
	}
}

Date::Date(const Date& other) : 
	m_day(other.m_day),
	m_month(other.m_month),
	m_year(other.m_year)
{
	if (!isValidDate(other.m_day, other.m_month, other.m_year)) {
		throw InvalidDate("The given date has invalid dates");
	}
}


Date Date::today() {
	time_t secondsSinceEpoch = time(0);
	struct tm* timer = localtime(&secondsSinceEpoch);
	return Date(timer->tm_mday, timer->tm_mon + 1, timer->tm_year + 1900);
}

Date::Date() {
	m_day = Date::today().day();
	m_month = Date::today().month();
	m_year = Date::today().year();
}

const int& Date::day() const {
	return m_day;
}

const int& Date::month() const {
	return m_month;
}

const int& Date::year() const {
	return m_year;
}

bool Date::isValidDate(const int& day, const int& month, const int& year) {
	struct tm timeStruct{};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;

	time_t time = mktime(&timeStruct);

	return time != -1 &&
		timeStruct.tm_year == year - 1900 &&
		timeStruct.tm_mon == month - 1 &&
		timeStruct.tm_mday == day;
}

Date& Date::operator=(const Date& other) {
	m_day = other.m_day;
	m_month = other.m_month;
	m_year = other.m_year;
	return *this;
}

Date Date::operator+(const Day& day) const {
	return handleTimeOperation(day.value, true);
}

Date operator+(const Day& day, const Date& date) {
	return date + day;
}

Date Date::operator+(const Week& week) const {
	return handleTimeOperation(static_cast<Day>(week).value, true);

}

Date operator+(const Week& week, const Date& date) {
	return date + week;
}

Date Date::operator+(const Year& year) const {
	return handleTimeOperation(static_cast<Day>(year).value, true);
}

Date operator+(const Year& year, const Date& date) {
	return date + year;
}

Date Date::operator-(const Day& day) const {
	return handleTimeOperation(day.value, false);
}

Date operator-(const Day& day, const Date& date) {
	return date - day;
}

Date Date::operator-(const Week& week) const {
	return handleTimeOperation(static_cast<Day>(week).value, false);

}

Date operator-(const Week& week, const Date& date) {
	return date - week;
}

Date Date::operator-(const Year& year) const {
	return handleTimeOperation(static_cast<Day>(year).value, false);
}

Date operator-(const Year& year, const Date& date) {
	return date - year;
}

bool Date::operator==(const Date& other) const {
	return m_day == other.m_day && m_month == other.m_month && m_year == other.m_year;
}

bool Date::operator!=(const Date& other) const {
	return !(*this == other);
}

bool Date::operator<(const Date& other) const {
	return (m_year < other.m_year) ||
		(m_year == other.m_year && m_month < other.m_month) ||
		(m_year == other.m_year && m_month == other.m_month && m_day < other.m_day);
}

bool Date::operator>(const Date& other) const {
	return other < *this;
}

bool Date::operator<=(const Date& other) const {
	return *this < other || *this == other;
}

bool Date::operator>=(const Date& other) const {
	return *this > other || *this == other;
}

Date::operator const char* () const {
	static std::string dateString;
	std::ostringstream outputString;
	outputString << m_day << " de " << months[m_month - 1] << " de " << m_year;
	dateString = outputString.str();
	return dateString.c_str();
}

std::ostream& operator<<(std::ostream& o, const Date& date) {
	o << date.year() << "/";
	if (date.month() < 10) o << "0";
	o << date.month() << "/";
	if (date.day() < 10) o << "0";
	o << date.day();
	return o;
}

Date Date::handleTimeOperation(const int& days, bool add) const {
	struct tm timeStruct {};
	timeStruct.tm_year = m_year - 1900;
	timeStruct.tm_mon = m_month - 1;
	timeStruct.tm_mday = add ? m_day + days : m_day - days;

	time_t time = mktime(&timeStruct);
	struct tm* newTime = localtime(&time); 
	return Date(newTime->tm_mday, newTime->tm_mon + 1, newTime->tm_year + 1900);
}