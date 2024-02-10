#include "MyString.h"
#include <cstring>
#include <stdexcept>
#include <utility>

static const char EOS = '\0';

MyString::MyString() : m_str(new char[1]), m_length(0) {
	m_str[0] = EOS;
}

MyString::MyString(size_t n) : m_str(new char[n + 1]), m_length(n) {
	m_str[n] = EOS;
}

MyString::MyString(size_t n, char c) : m_str(new char[n + 1]), m_length(n) {
	for (size_t i = 0; i < n; i++) {
		m_str[i] = c;
	}
	m_str[n] = EOS;
}

MyString::MyString(const char* str) : m_str(nullptr), m_length(strlen(str)) {
	m_str = new char[m_length + 1];
	strcpy(m_str, str);
	
}

MyString::MyString(const MyString& other) : m_str(new char[other.m_length + 1]), m_length(other.m_length) {
	strcpy(m_str, other.m_str);
}
 
MyString::~MyString() {
	delete[] m_str;
}

const char* MyString::c_str() const {
	return m_str;
}

size_t MyString::length() const {
	return m_length;
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		delete[] m_str;
		m_length = other.m_length;
		m_str = new char[m_length + 1];
		strcpy(m_str, other.m_str);
	}
	return *this;
}

MyString& MyString::operator=(const char* str) {
	if (m_str != str) {
		delete[] m_str;
		m_length = strlen(str);
		m_str = new char[m_length + 1];
		strcpy(m_str, str);
	}
	return *this;
}

bool MyString::operator==(const MyString& other) const {
	if (m_length != other.m_length) {
		return false;
	}
	for (size_t i = 0; i < m_length; i++) {
		if (m_str[i] != other.m_str[i]) {
			return false;
		}
	}
	return true;
}

bool operator==(const char* str, const MyString other) {
	return other == str;
}

bool MyString::operator!=(const MyString& other) const {
	return !(*this == other);
}

bool MyString::operator<(const MyString& other) const {
	for (size_t i = 0; i < m_length && i < other.m_length; i++) {
		if (m_str[i] < other.m_str[i]) {
			return true;
		}
		else if (m_str[i] > other.m_str[i]) {
			return false;
		}
	}
	return m_length < other.m_length;
}

bool MyString::operator>(const MyString& other) const {
	return other < *this;
}

bool MyString::operator<=(const MyString& other) const {
	return (*this < other) || (*this == other);
}

bool MyString::operator>=(const MyString& other) const {
	return (*this > other) || (*this == other);
}

MyString MyString::operator+(const MyString& other) const {
	return *this + other.c_str();
}

MyString MyString::operator+(const char* str) const {
	MyString newStr(m_length + strlen(str));
	strcpy(newStr.m_str, m_str);
	strcat(newStr.m_str, str);
	return newStr;
}

MyString MyString::operator+=(const MyString& other) {
	return *this += other.c_str();
}

MyString MyString::operator+=(const char* str) {
	char* tempStr = new char[m_length + strlen(str) + 1];
	cleanAndAdd(tempStr, str);
	return *this;
}

const char& MyString::operator[](size_t index) const {
	return m_str[index];
}

char& MyString::operator[](size_t index) {
	return m_str[index];
}

const char& MyString::at(size_t index) const {
	if (index > m_length) {
		throw std::out_of_range("Index out of bounds");
	}
	return m_str[index];
}
char& MyString::at(size_t index) {
	if (index > m_length) {
		throw std::out_of_range("Index out of bounds");
	}
	return m_str[index];
}

MyString MyString::substr(size_t pos, size_t len) const {
	if (pos > m_length) {
		throw std::out_of_range("Position out of bounds");
	}
	if (pos + len > m_length) {
		len = m_length - pos;
	}
	MyString subStr(len);
	for (size_t i = 0; i < len; i++) {
		subStr.m_str[i] = m_str[pos + i];
	}
	subStr.m_str[len] = EOS;
	return subStr;
}

void MyString::cleanAndAdd(char* temp, const char* other) {
	strcpy(temp, m_str);
	strcat(temp, other);
	delete[] m_str;
	m_str = temp;
	m_length += strlen(other);
}

MyString& MyString::operator=(MyString&& other) noexcept {
	if (this != &other) {
		delete[] m_str;
		m_length = other.m_length;
		m_str = other.m_str;
		other.m_length = 0;
		other.m_str = nullptr;
	}
	return *this;
}

MyString::MyString(MyString&& other) noexcept {
	*this = std::move(other);
}



