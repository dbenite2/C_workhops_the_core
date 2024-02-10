#pragma once

struct Day {
	int value{0};
	explicit Day(const int& newVal) : value(newVal) {}
	operator int() const { return value; }
};
struct Week {
	int value{0};
	explicit Week(const int& newVal) : value(newVal) {}
	operator Day() const { return Day(value * 7); }
	operator int() const { return value; }
};
struct Year {
	int value{0};
	explicit Year(const int& newVal) : value(newVal) {}
	operator Day() const { return Day(value * 365); }
	operator Week() const { return Week(value * 52); }
	operator int() const { return value; }
};

class Date {
public:
	class InvalidDate {
	public:
		InvalidDate(const char* reason): m_reason(reason) {}

		const char* reason() const {
			return m_reason;
		}

	private:
		const char* m_reason;
	};

	Date(const int& day,const int& month,const int& year);
	Date(const char* dateFormat);
	Date(const Date& other);
	Date();

	Date& operator=(const Date& other);
	Date operator+(const Day& day) const;
	Date operator+(const Week& week) const;
	Date operator+(const Year& year) const;
	Date operator-(const Day& day) const;
	Date operator-(const Week& week) const;
	Date operator-(const Year& year) const;

	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator>=(const Date& other) const;

	explicit operator const char* () const;

	friend std::ostream& operator<<(std::ostream& o, const Date& date);

	const int& day() const;
	const int& month() const;
	const int& year() const;
	static Date today();

private:
	int m_day{0};
	int m_month{0};
	int m_year{0};
	bool isValidDate(const int& day, const int& month, const int& year);
	Date handleTimeOperation(const int& days, bool add) const;

};