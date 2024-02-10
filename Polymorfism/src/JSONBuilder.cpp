#include <iostream>;
#include "JSONBuilder.h";

const char* const JSONBuilder::OBJECT_START_CHARACTER{ "{" };
const char* const JSONBuilder::OBJECT_END_CHARACTER{ "}" };
const char* const JSONBuilder::ARRAY_START_CHARACTER{ "[" };
const char* const JSONBuilder::ARRAY_END_CHARACTER{ "]" };
const char* const JSONBuilder::TAB_CHARACTER{ "\t" };
const char* const JSONBuilder::NEW_LINE_CHARACTER{ "\n" };
const char* const JSONBuilder::SEPERATOR_CHARACTER{ " : " };
const char* const JSONBuilder::NEW_PAIR_CHARACTER{ "," };
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
	m_ss << m_indent;
}

void JSONBuilder::increaseIndent() {
	m_indent += " ";
}

void JSONBuilder::decreaseIndent() {
	if (m_indent.size() > 2) m_indent.pop_back();
	m_indent.pop_back();
}

void JSONBuilder::writeCString(const char* key, const char* value, bool hasNext) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER <<  SEPERATOR_CHARACTER << QUOTE_CHARACTER << value << QUOTE_CHARACTER;
	if (hasNext) m_ss << NEW_PAIR_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::writeInt(const char* key, const uint64_t& value, bool hasNext) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER << SEPERATOR_CHARACTER << std::to_string(value).c_str();
	if (hasNext) m_ss << NEW_PAIR_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::writeDouble(const char* key, const double& value, bool hasNext) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER << SEPERATOR_CHARACTER << std::to_string(value).c_str();
	if (hasNext) m_ss << NEW_PAIR_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::startArray(const char* key) {
	writeIdentation();
	m_ss << QUOTE_CHARACTER << key << QUOTE_CHARACTER << SEPERATOR_CHARACTER << ARRAY_START_CHARACTER;
}

void JSONBuilder::endArray(bool hasNext) {
	m_ss << ARRAY_END_CHARACTER;
	if (hasNext) m_ss << NEW_PAIR_CHARACTER;
	m_ss << NEW_LINE_CHARACTER;
}

void JSONBuilder::addArrayElement(const std::string& value,bool firstElement, bool hasNext) {
	if (!firstElement) writeIdentation();
	m_ss << value;
	if (hasNext) m_ss << NEW_PAIR_CHARACTER;
	if (firstElement) m_ss << NEW_LINE_CHARACTER;
}

std::string JSONBuilder::build() {
	return m_ss.str();
}
