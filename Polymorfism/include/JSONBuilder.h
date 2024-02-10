#pragma once

#include <sstream>
#include <string>

class JSONBuilder {
public:
	JSONBuilder();
	void startObject();
	void endObject();
	void increaseIndent();
	void decreaseIndent();
	void writeCString(const char* key, const char* value, bool hasNext);
	void writeInt(const char* key, const uint64_t& value, bool hasNext);
	void writeDouble(const char* key, const double& value, bool hasNext);
	void startArray(const char* key);
	void endArray(bool hasNext);
	void addArrayElement(const std::string& value, bool firstElement, bool hasNext);
	std::string build();
private:

	std::stringstream m_ss;
	std::string m_indent;

	static const char* const OBJECT_START_CHARACTER;
	static const char* const OBJECT_END_CHARACTER;
	static const char* const ARRAY_START_CHARACTER;
	static const char* const ARRAY_END_CHARACTER;
	static const char* const TAB_CHARACTER;
	static const char* const NEW_LINE_CHARACTER;
	static const char* const SEPERATOR_CHARACTER;
	static const char* const NEW_PAIR_CHARACTER;
	static const char* const QUOTE_CHARACTER;
	size_t indentLevel{ 0 };

	void writeIdentation();

};