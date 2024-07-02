#include "ConsoleIO.h"

void ConsoleIO::TextAppend(const std::string& uuid, const std::string& text)
{
	printf("[%s]  %s\n", uuid.c_str(), text.c_str());
}

void ConsoleIO::TextSet(const std::string& uuid, const std::string& text)
{
	os->GetConsole()->clear();
	printf("[%s]  %s\n", uuid.c_str(), text.c_str());
}

void ConsoleIO::OnPanic(int code)
{
	os->GetConsole()->pause();
}
