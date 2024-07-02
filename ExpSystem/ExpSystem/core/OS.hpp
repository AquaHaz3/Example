#pragma once
#include <stdlib.h>
#include <string>


struct OSConsole {

	virtual void clear() {};
	virtual void pause() {};

};

class OS
{
public:

	OS() { console = 0; };

	virtual OSConsole* GetConsole() = 0;
	virtual void Exit(int code) = 0;
	virtual void ExtraPanic(const char* msg, int code) = 0;
	virtual void SleepT(__int64 mills) = 0;

protected:

	OSConsole* console;

};

namespace Platform {

	OS* GetCurrentOS();
	OS* GetOS(const std::string& name);

}

// Implementation:

#ifdef _WIN32
//...
#endif

struct WinConsole : OSConsole {

	virtual void clear() { system("cls"); };
	virtual void pause() { system("pause"); };
};

class WindowsOS : public OS {

public:

	WindowsOS() : OS() {
		console = new WinConsole();
	};

	~WindowsOS() {
		if(console != 0) delete console;
	}

	virtual OSConsole* GetConsole() override;
	virtual void Exit(int code) override;
	virtual void ExtraPanic(const char* msg, int code) override;
	virtual void SleepT(__int64 mills) override;

};

