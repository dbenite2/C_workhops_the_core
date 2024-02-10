#pragma once

class MyString {
public:
	MyString();
	MyString(size_t n);
	MyString(size_t n, char c);
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;
	~MyString();
	MyString& operator=(const MyString& other);
	MyString& operator=(const char* str);
	MyString& operator=(MyString&& other) noexcept;

	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>=(const MyString& other) const;

	MyString operator+(const MyString& other) const;
	MyString operator+(const char* str) const;
	MyString operator+=(const MyString& other);
	MyString operator+=(const char* str);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	const char& at(size_t index) const;
	char& at(size_t index);

	const char* c_str() const;
	size_t length() const;
	MyString substr(size_t pos, size_t len) const;
	
private:
	char* m_str{nullptr};
	size_t m_length{ 0 };
	void cleanAndAdd(char* temp, const char* other);
};