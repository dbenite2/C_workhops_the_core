#include <iostream>;
#include "JSONBuilder.h";

const char* const JSONBuilder::OBJECT_START_CHARACTER{ "{" };
const char* const JSONBuilder::OBJECT_END_CHARACTER{ "}" };
const char* const JSONBuilder::ARRAY_START_CHARACTER{ "[" };
const char* const JSONBuilder::ARRAY_END_CHARACTER{ "]" };
const char* const JSONBuilder::TAB_CHARACTER{ "\t" };
const char* const JSONBuilder::NEW_LINE_CHARACTER{ "\n" };
const char* const JSONBuilder::SEPERATOR_CHARACTER{ " : " };
const char* const JSONBuilder::COMMA_CHARACTER{ "," };
const char* const JSONBuilder::SPACED_COMMA_CHARACTER{ ", " };
const char* const JSONBuilder::QUOTE_CHARACTER{ "\"" };

JSONBuilder::JSONBuilder() : m_indent(" ") {}

void JSONBuilder::startObject() {
	m_ss << OBJECT_START_CHARACTER << NEW_LINE_CHARACTER;
	increaseIndent();
}

void JSONBuilder::endObject() {
	decreaseIndent();
	m_ss << OBJECT_END_CHARACTER;
}

void JSONBuilder::writeIdentation() {
	for (size_t i = 0; i < indentLevel; i++) {
		m_ss << TAB_CHARACTER;
	}
}

void JSONBuilder::increaseIndent() {
	indentLevel++;
}

void JSONBuilder::decreaseIndent() {
	if (indentLevel < 0) return;
	indentLevel--;
}

void JSONBuilder::writeCString(const char* key, const char* value, bool hasNext) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER <<  SEPERATOR_CHARACTER << QUOTE_CHARACTER << value << QUOTE_CHARACTER;
	if (hasNext) m_ss << COMMA_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::writeInt(const char* key, const uint64_t& value, bool hasNext) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER << SEPERATOR_CHARACTER << value;
	if (hasNext) m_ss << COMMA_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::writeDouble(const char* key, const double& value, bool hasNext) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER << SEPERATOR_CHARACTER << value;
	if (hasNext) m_ss << COMMA_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::startArray(const char* key) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER << SEPERATOR_CHARACTER << ARRAY_START_CHARACTER;
}

void JSONBuilder::endArray(bool hasNext) {
	m_ss << ARRAY_END_CHARACTER;
	if (hasNext) m_ss << COMMA_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::addArrayElement(const double& valueX, const double& valueY, const size_t& index, bool hasNext) {
	if (index != 0 && index % 2 != 0) writeIdentation();
	m_ss << ARRAY_START_CHARACTER << valueX << SPACED_COMMA_CHARACTER << valueY << ARRAY_END_CHARACTER;
	if (hasNext) m_ss << SPACED_COMMA_CHARACTER;
	if ((index == 0 || index % 2 == 0) && hasNext) m_ss << NEW_LINE_CHARACTER;
}

std::string JSONBuilder::build() {
	return m_ss.str();
}
