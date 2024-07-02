#include "Launcher.h"
#include "core/ExpSystem.h"
#include "core/CrackMe.h"

Launcher::Launcher()
{
}

#include "core/design/ConsoleIO.h"

void Launcher::Launch(AppDesign design)
{
	using enum AppDesign;

	CrackMe crackme = CrackMe();

	switch (design)
	{
	case Console:
		ExpSystem::GetInstance()->Init(new ConsoleIO());
		crackme.Start();
		break;
	default:
		Platform::GetCurrentOS()->ExtraPanic("Can't init ExpSystem: Unknown app design!", -2);
		return;
	}
	ExpSystem::GetInstance()->Start();
}
