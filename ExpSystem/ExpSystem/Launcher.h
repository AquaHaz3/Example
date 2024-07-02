#pragma once

#include <string>

enum class AppDesign
{
	Console = 0,
	RayLib = 1,
};

class Launcher
{

public:

	Launcher();
	void Launch(AppDesign design);

};

