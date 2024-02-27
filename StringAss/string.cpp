#include "String.h"
#include <cstring>
#include <cctype>
#include <iostream>

String::String():m_str(nullptr), m_length(0), m_capacity(0)
{

}

String::String(const char* _str)
{
	m_length = strlen(_str);
	m_capacity = m_length + 1;
	m_str = new char[m_capacity];
	strcpy(m_str, _str);
}

String::String(const String& _other)
{
	m_length = _other.m_length;
	m_capacity = _other.m_capacity;
	m_str = new char[m_capacity];
	strcpy(m_str, _other.m_str);
}

String::~String()
{
	delete[] m_str;
}

size_t String::Length() const
{
	return m_length;
}

char& String::CharacterAt(size_t _index)
{
	// Ensure that the index is within bounds
	if (_index >= m_length) {
		static char nullChar = '\0'; // Static variable to avoid returning a reference to a local variable
		return nullChar;
	}
	return m_str[_index];
}

const char& String::CharacterAt(size_t _index) const
{
	// Ensure that the index is within bounds
	if (_index >= m_length) {
		static const char nullChar = '\0'; // Static variable to avoid returning a reference to a local variable
		return nullChar;
	}
	return m_str[_index];
}

bool String::EqualTo(const String& _other) const
{
	// If the lengths are different strings not equal
	if (m_length != _other.m_length) {
		return false;
	}

	// Compare each character in both strings
	for (size_t i = 0; i < m_length; ++i) {
		if (m_str[i] != _other.m_str[i]) {
			// If any characters are different strings not equal
			return false;
		}
	}

	// All characters are equal, the strings are equal
	return true;
}

String& String::Append(const String& _str)
{
	// Calculate the new length of the string
	size_t newLength = m_length + _str.m_length;

	// If not enough capacity resize the string
	if (newLength >= m_capacity) {
		// Calculate the new capacity
		size_t newCapacity = newLength + 1; // +1 for the null terminator

		char* newStr = new char[newCapacity]; // Allocate a new buffer with the new capacity
		strcpy(newStr, m_str);
		strcat(newStr, _str.m_str);

		// Delete old buffer
		delete[] m_str;

		// Update pointer and capacity
		m_str = newStr;
		m_capacity = newCapacity;
	}
	else {
		// Append the string to be appended (_str) to the current buffer
		strcat(m_str, _str.m_str);
	}

	// Update the length
	m_length = newLength;

	// Ensure null-termination
	m_str[newLength] = '\0';

	// Return a reference to this object to allow chaining
	return *this;
}


String& String::Prepend(const String& _str)
{
	// Calculate the new length of the string
	size_t newLength = m_length + _str.m_length;
	// Calculate the new capacity
	if (newLength >= m_capacity) {
		size_t newCapacity = newLength + 1; // +1 for the null terminator

		char* newStr = new char[newCapacity]; // Allocate a new buffer with the new capacity
		strcpy(newStr, _str.m_str);
		strcat(newStr, m_str);

		// Delete old buffer
		delete[] m_str;

		//Update pointer and capacity
		m_str = newStr;
		m_capacity = newCapacity;
	}
	else {
		memmove(m_str + _str.m_length, m_str, m_length + 1);
		memcpy(m_str, _str.m_str, _str.m_length);
	}
	m_length = newLength;
	return *this;
}

const char* String::CStr() const
{
	return m_str;
}

String& String::ToLower()
{
	for (size_t i = 0; i < m_length; ++i) {
		m_str[i] = tolower(m_str[i]);
	}
	return *this;
}

String& String::ToUpper()
{
	for (size_t i = 0; i < m_length; ++i) {
		m_str[i] = toupper(m_str[i]);
	}
	return *this;
}

size_t String::Find(const String& _str)
{
	// Use strstr to find the first occurrence of _str in m_str
	const char* result = strstr(m_str, _str.m_str);

	// If result is null, _str is not found in m_str
	if (result == nullptr) {
		return static_cast<size_t>(-1); // Return -1 to indicate not found
	}

	// Calculate the index of the found substring
	return static_cast<size_t>(result - m_str);
}

size_t String::Find(size_t _startIndex, const String& _str)
{
	// Check if the start index is valid
	if (_startIndex >= m_length) {
		return static_cast<size_t>(-1);
	}

	// Use strstr to find the first occurrence of _str in m_str starting from _startIndex
	const char* result = strstr(m_str + _startIndex, _str.m_str);

	// If _str is not found in m_str
	if (result == nullptr) {
		return static_cast<size_t>(-1); // Return -1 to indicate not found
	}

	// Find index of the found substring relative to the start index
	return static_cast<size_t>(result - m_str);
}

String& String::Replace(const String& _find, const String& _replace)
{
	// find first occurance of _find
	size_t index = Find(_find);

	// if not found return
	if(index == static_cast<size_t>(-1)) {
		return *this;
	}

	size_t newLength = m_length - _find.m_length + _replace.m_length;
	
	//check length and capacity
	if(newLength >= m_capacity) {
		size_t newCapacity = newLength + 1;
		char* newStr = new char[newCapacity];
		strcpy(newStr, m_str);
		strcpy(newStr + index, _replace.m_str);
		strcpy(newStr + index + _replace.m_length, m_str + index + _find.m_length);
		delete[] m_str;
		m_str = newStr;
		m_capacity = newCapacity;
	} else {
		memmove(m_str + index + _replace.m_length, m_str + index + _find.m_length, m_length - index - _find.m_length + 1);
		memcpy(m_str + index, _replace.m_str, _replace.m_length);
	}

	m_length = newLength;

	return *this;
}

String& String::ReadFromConsole()
{
	// Prompt the user to enter a string
	std::cout << "Enter a string: ";

	// Allocate memory for the string
	size_t bufferSize = 256; // Initial buffer size
	char* buffer = new char[bufferSize];
	size_t index = 0;

	// Read characters from the console until a newline is encountered
	char ch;
	while (std::cin.get(ch) && ch != '\n') {
		// Resize the buffer if needed
		if (index >= bufferSize - 1) {
			// Allocate a new buffer with double the size
			char* newBuffer = new char[bufferSize * 2];
			// Copy the existing content to the new buffer
			memcpy(newBuffer, buffer, bufferSize);
			// Delete the old buffer
			delete[] buffer;
			// Update the buffer pointer and size
			buffer = newBuffer;
			bufferSize *= 2;
		}
		// Store the character in the buffer
		buffer[index++] = ch;
	}

	// Null-terminate the string
	buffer[index] = '\0';

	// Copy the buffer content to the String object
	size_t inputLength = strlen(buffer);
	if (inputLength >= m_capacity) {
		// Reallocate memory if needed
		delete[] m_str;
		m_capacity = inputLength + 1;
		m_str = new char[m_capacity];
	}
	strcpy(m_str, buffer);
	m_length = inputLength;

	// Return a reference to this object
	return *this;
}

String& String::WriteToConsole()
{
	std::cout << m_str;
	return *this;
}

bool String::operator==(const String& _other)
{
	return EqualTo(_other);
}

bool String::operator!=(const String& _other)
{
	return !EqualTo(_other);
}

String& String::operator=(const String& _other)
{
	//Check for self assignment
	if (this != &_other) {
		delete[] m_str; // Delete old content

		// Copy new content
		m_length = _other.m_length;
		m_capacity = _other.m_capacity;
		m_str = new char[m_capacity];
		strcpy(m_str, _other.m_str);
	}
	return *this;
}

char& String::operator[](size_t _index)
{
	// Ensure that the index is within bounds
	if (_index >= m_length) {
		static char nullChar = '\0';
		return nullChar;
	}

	return m_str[_index];
}

const char& String::operator[](size_t _index) const {
	// Ensure that the index is within bounds
	if (_index >= m_length) {
		static char nullChar = '\0';
		return nullChar;
	}

	return m_str[_index];
}

bool String::operator<(String& _other)
{
	return strcmp(m_str, _other.m_str) < 0;
}

const bool String::operator<(const String& _other) const {
	return strcmp(m_str, _other.m_str) < 0;
}


String String::operator+(const String& _str) const {
	String result(*this);
	result.Append(_str);
	return result; // Return by value, not by reference
}

String& String::operator+=(const String& _str) {
	Append(_str);
	return *this;
}