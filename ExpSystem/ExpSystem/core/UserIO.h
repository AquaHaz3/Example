#pragma once
#include <string>
#include "OS.hpp"

class UserIO
{
public:

	UserIO() { os = Platform::GetCurrentOS(); }

	virtual void TextAppend(const std::string& uuid, const std::string& text) = 0;
	virtual void TextSet(const std::string& uuid, const std::string& text) = 0;

	virtual void OnPanic(int code) = 0;

	void log(std::string text);
	void log_error(std::string text);
	void panic(std::string text, int code);

protected:

	OS* os = nullptr;

};

