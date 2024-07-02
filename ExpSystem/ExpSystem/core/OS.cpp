#include "OS.hpp"

#ifdef _WIN32
#include <Windows.h>
#define _IN_WIN(code) {code;}
#else
#define _IN_WIN(code)
#endif

OS* Platform::GetCurrentOS()
{
#ifdef _WIN32
	return GetOS("win");
#endif
	throw new std::exception("Unknown operation system...");
}

OS* Platform::GetOS(const std::string& name)
{
	if (name == "windows" || name == "win") {
		return new WindowsOS();
	}
	std::string err_msg = "Can't find os with name(tag): " + name;
	throw new std::exception(err_msg.c_str());
	return 0;
}

OSConsole* WindowsOS::GetConsole()
{
	return console;
}

void WindowsOS::Exit(int code)
{
	_IN_WIN(ExitProcess(code));
}

void WindowsOS::ExtraPanic(const char* msg, int code)
{
	_IN_WIN(
		MessageBoxA(0, msg, "[EXTRA] Fatal error", MB_ICONERROR);
		ExitProcess(code);
	)
}

void WindowsOS::SleepT(__int64 mills)
{
	_IN_WIN(Sleep(mills))
}
