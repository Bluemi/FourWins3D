#include "Debug.hpp"

#include <iostream>

Debug::DebugClass Debug::out;

Debug::DebugClass::DebugClass()
{
	strings_.push_back("");
	fileWriter.open(LOG_FILE_NAME, std::ios::out | std::ios::trunc);
}

Debug::DebugClass::~DebugClass()
{
	for (auto iter = strings_.begin(); iter != strings_.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
	fileWriter.close();
}

Debug::DebugClass& Debug::DebugClass::operator<<(const int i)
{
	appendString(std::to_string(i));
	return *this;
}

Debug::DebugClass& Debug::DebugClass::operator<<(const float f)
{
	appendString(std::to_string(f));
	return *this;
}

Debug::DebugClass& Debug::DebugClass::operator<<(const std::string s)
{
	appendString(s);
	return *this;
}

Debug::DebugClass& Debug::DebugClass::operator<<(const Debug::Tag tag)
{
	switch (tag)
	{
		case Debug::Tag::endl:
		{
			appendColor(DEFAULT_COLOR);
			strings_.push_back("");
			fileWriter << std::endl;
			break;
		}
		case Debug::Tag::error:
		{
			appendColor(ERROR_COLOR);
			appendString("ERROR: ");
			break;
		}
		case Debug::Tag::warn:
		{
			appendColor(WARN_COLOR);
			appendString("WARN : ");
			break;
		}
		case Debug::Tag::note:
		{
			appendColor(NOTE_COLOR);
			appendString("NOTE : ");
			break;
		}
		case Debug::Tag::test:
		{
			appendColor(TEST_COLOR);
			appendString("TEST : ");
			break;
		}
	}
	return *this;
}

void Debug::DebugClass::appendColor(std::string c)
{
	strings_.back().append(c);
}

void Debug::DebugClass::appendString(std::string s)
{
	strings_.back().append(s);
	fileWriter << s;
}
