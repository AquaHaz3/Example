#pragma once
#include "../UserIO.h"

class ConsoleIO : public UserIO
{

public:

	ConsoleIO() : UserIO() {};

	virtual void TextAppend(const std::string& uuid, const std::string& text) override;
	virtual void TextSet(const std::string& uuid, const std::string& text) override;

	virtual void OnPanic(int code) override;

};

