#include "UserIO.h"

void UserIO::log(std::string text)
{
	TextAppend("LOG", text);
}

void UserIO::log_error(std::string text)
{
	TextAppend("ERROR", text);
}

void UserIO::panic(std::string text, int code)
{
	TextAppend("FATAL_ERROR", text);
	OnPanic(code);
	exit(code);
}
